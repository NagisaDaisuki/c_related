#include <functional> // std::function 能装下 "任何可调用对象"
#include <iostream>
#include <memory> // std::unique_ptr , std::make_unique

namespace Foo::Goo {
int add(int x, int y) { return x + y; }
} // namespace Foo::Goo

namespace V2 {
int add(int x, int y) { return x + y; }
} // namespace V2

// 如何在运行期"切换"一个命名空间
// 1. 函数指针(最轻量的运行期切换)
int (*active_add)(int, int) = Foo::Goo::add;
// 2. std::function 能装下"任何可调用对象"
std::function<int(int, int)> active_add_func = Foo::Goo::add;

// 4.1 模板参数直接传"策略"
struct GooPolicy {
  static int add(int x, int y) { return Foo::Goo::add(x, y); }
};

struct V2Policy {
  static int add(int x, int y) { return V2::add(x, y); }
};

template <typename Policy> struct Calculator {
  int add(int x, int y) const { return Policy::add(x, y); }
};
// 4.2 模板函数 if constexpr 在编译期分支
enum class Impl { Goo, V2 };
template <Impl I> int add(int x, int y) {
  if constexpr (I == Impl::Goo) { // C++17 if constexpr
                                  // 编译期时执行,未被选中的分支不会被实例化
    return Foo::Goo::add(x, y);   // 写"对某些类型才合法"的代码
  } else {
    return V2::add(x, y);
  }
}
// 4.3 用函数模板 + 传函数对象
template <typename F> int apply(F f, int x, int y) { return f(x, y); }
#ifndef TEMPLATE
#define TEMPLATE
#endif
int main() {
#if defined(FP)
  namespace Active =
      Foo::Goo; // active now refers to Foo::Goo 编译期的名字替换规则
  std::cout << Active::add(1, 2) << '\n'; // This is really Foo::Goo::add()
  std::cout
      << active_add(1, 2)
      << '\n'; // This is also really Foo::Goo::add() represented by active_add
  // Active = V2; 这里不能重新赋值,因为 namespace根本不是对象
  active_add = V2::add; // 这样可以,因为是函数指针变量

  std::cout << active_add(2, 2) << '\n';
#elif defined(FUNC)
  std::cout << active_add_func(2, 3) << '\n';

  int factor = 10; // 捕获外部状态
  active_add_func = [factor](int x, int y) { return (x + y) * factor; };

  std::cout << active_add_func(2, 3) << '\n'; // 50

  active_add_func = V2::add;
  std::cout << active_add_func(2, 3) << '\n'; // 6
#elif defined(VFUNC)
  struct IAdd {
    virtual int add(int x, int y) const = 0;
    virtual ~IAdd() = default;
  };

  struct GooAdd : IAdd {
    int add(int x, int y) const override { return Foo::Goo::add(x, y); }
  };

  struct V2Add : IAdd {
    int add(int x, int y) const override { return V2::add(x, y); }
  };

  GooAdd goo;
  V2Add v2;

  const IAdd *active = &goo;
  std::cout << active->add(2, 3) << '\n';

  active = &v2; // 运行期切换
  std::cout << active->add(2, 4) << '\n';

  // 动态分配所有权
  std::unique_ptr<IAdd> active_dyna = std::make_unique<GooAdd>();
  std::cout << active_dyna->add(2, 3) << '\n'; // 5
  active_dyna = std::make_unique<V2Add>();
  std::cout << active_dyna->add(2, 3) << '\n';

#elif defined(TEMPLATE)
  Calculator<GooPolicy> c1;
  Calculator<V2Policy> c2;
  std::cout << c1.add(2, 3) << '\n';
  std::cout << c2.add(2, 3) << '\n';

  std::cout << add<Impl::Goo>(2, 3) << '\n';
  std::cout << add<Impl::V2>(2, 3) << '\n';

  std::cout << apply(Foo::Goo::add, 2, 3) << '\n';
  std::cout << apply(V2::add, 2, 3) << '\n';

  int factor = 10;
  std::cout << apply([factor](int x, int y) { return (x + y) * factor; }, 2, 3)
            << std::endl;
#endif
  return 0;
}