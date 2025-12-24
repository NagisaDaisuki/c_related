#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>


class HasPtr
{
    friend void swap(HasPtr&,HasPtr&);
public:
    HasPtr(const std::string &s = std::string()) :
      ps(new std::string(s)),i(0) {}
    HasPtr(const HasPtr &p) :
      ps(new std::string(*p.ps)),i(p.i) {}
    HasPtr& operator=(const HasPtr&);
    HasPtr& operator=(HasPtr);
    ~HasPtr(){ delete ps; }
private:
    std::string *ps;
    int i;

};

/*
    swap函数应该调用swap，而不是std::swap
    如果一个类的成员有自己类型特定的swap,那么调用std::swap就是
    错误的
*/
inline
void swap(HasPtr& lhs,HasPtr& rhs)
{
    using std::swap;
    swap(lhs.ps,rhs.ps); //交换string指针而不是string的值
    swap(lhs.i,rhs.i); //交换int成员
}

HasPtr& HasPtr::operator=(const HasPtr& h)
{
  //when executing assignment_operator need to destory
  //lvalue resources first
  auto newp = new std::string(*h.ps);
  delete ps;
  ps = newp;
  i = h.i;
  return *this;
}

/*
    定义swap的类通常用swap来定义赋值运算符
    这些运算符使用了一种名为**拷贝并交换**的技术
    这种技术将左侧运算对象与右侧运算对象的一个副本进行交换

    使用swap自动处理了自赋值情况且天然就是异常安全的
    ，通过在改变左侧运算对象之前拷贝右侧运算对象保证了自赋值的安全
*/
HasPtr& HasPtr::operator=(HasPtr rhs) //operator=的重载版本
{
  swap(*this,rhs); //rhs 是传拷贝
  return *this;
}

int main()
{
    /*交换操作*/
    /*
        除了定义拷贝控制成员,管理资源的类通常还定义一个名为swap的函数
    */
    return 0;
}
