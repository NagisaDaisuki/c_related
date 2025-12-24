#include <cassert>
#include <iostream>
#include <memory>

struct Foo
{
  Foo() { std::cout << "Foo\n"; }
  ~Foo() { std::cout << "~Foo\n"; }
};

// ownership of the Foo resource is transferred when calling this function
void legacy_api(Foo* owning_foo)
{
  std::cout << __func__ << '\n';

  delete owning_foo;
}

int main()
{
  std::unique_ptr<Foo> managed_foo(new Foo);
  // 可能包括返回或抛异常逻辑的代码
  legacy_api(managed_foo.release()); // 释放被管理对象的所有权

  assert(managed_foo == nullptr);

  return 0;
}
