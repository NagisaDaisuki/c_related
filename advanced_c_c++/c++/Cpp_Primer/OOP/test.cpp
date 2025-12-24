#include <iostream>

class Base{
  public:
    std::size_t size() const { return n; }
  protected:
    std::size_t n;
};

class Derived : private Base //使用私有继承
{
  public:
    //保持对象尺寸相关的成员的访问级别
    using Base::size;
  protected:
    using Base::n;
};
/*
    因为Derived使用了私有继承，所以继承而来的成员size和n(在默认情况下)
    是derived的私有成员。然而，我们使用using声明语句改变了这些成员的可访问性
    改变之后，Derived的**用户**将可以使用size成员，derived的派生类将能使用n
*/
