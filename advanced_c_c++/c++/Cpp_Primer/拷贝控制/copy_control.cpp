#include <vector>
#include <memory>
#include <string>
#include <iostream>

/*
  一个类通常通过定义五个特殊的成员函数来控制这些操作
  包括拷贝构造函数、移动构造函数、拷贝赋值符、移动赋值符和析构函数
    拷贝和移动构造函数定义了当用同类型的另一个对象初始化当前对象时做什么
    拷贝和移动赋值运算符定义了将一个对象赋予同类型的另一个对象时做什么

*/

/*
  直接初始化(Direct Initialization): 
    直接初始化时通过使用圆括号进行初始化的一种方式
    T obj(arg1,arg2,...);
  拷贝初始化(Copy Initialization)
    拷贝初始化是通过使用等号进行初始化的一种方式
    T obj = T(arg1,arg2,...);
  
    -从最终创建的对象来看，直接初始化和拷贝初始化的结果是相同的
  都是创建了一个对象并调用了相应的构造函数
    -语法上的区别在于使用圆括号还是等号，直接初始化使用圆括号，
  拷贝初始化使用等号
    -在现代编译器下，通常能够对这两种初始化方式进行优化，因此性能上的差异较小
  拷贝初始化可能涉及临时对象的创建和拷贝，但编译器通常能够进行优化以避免不必要
  的拷贝
  
  tips：当使用初始化标准库容器或者调用insert和push成员时，容器会对其元素进行拷贝初始化
  调用emplace成员时会进行直接初始化
*/

/*
  拷贝赋值运算符
    与类控制其对象如何初始化一样，类也可以控制器其对象如何赋值：
    Sales_data trans,accum;
    trans = accum; //将一个对象赋予同类型的另一个对象

  重载赋值运算符
    重载运算符本质上是函数，其名字由operator关键字后接表示要定义的运算符的符号组成
    赋值运算符就是一个名为operator=的函数
  
  重载运算符的参数表示运算符的运算对象
    某些运算符，包括赋值运算符，必须定义为成员函数
    如果一个运算符是一个成员函数，其左侧运算对象就绑定在到隐式的
    *this参数。对于一个二元运算符例如赋值运算符，其右值运算对象作为显示参数传递
*/

/*
  析构函数
    析构函数执行与构造函数相反的操作：构造函数初始化对象的非static数据成员
    还可能做一些其他工作。析构函数释放对象使用的资源，并销毁对象的非static数据成员
  *由于析构函数不接收参数，因此它不能被重载。对于一个给定类，只会有唯一一个析构函数*
*/

/*
   //定义四个Sales_data对象
  {
    Sales_data *p = new Sales_data; //p是一个内置指针
    auto p2 = std::make_shared<Sales_data>(); //p2是一个shared_ptr
    Sales_data item(*p); //拷贝构造函数将*p拷贝到item中
    std::vector<Sales_data> vec; //局部对象
    vec.push_back(*p); //拷贝p2所指向的对象
    delete p; //对p指向的对象调用析构函数
  }
  //退出局部作用域；对item、p2和vec调用析构函数
  //销毁p2会递减其引用计数；如果引用计数变为0，对象被释放
  //销毁vec会销毁它的元素
*/

/*
  合成析构函数
    当一个类未定义自己的析构函数时，编译器会为他定义一个合成析构函数(synthesized destructor)
    类似拷贝构造函数和拷贝构造运算符，对于某些类，合成析构函数被用来阻止该类型的对象被销毁
*/
class Resource{
  public:
    Resource()
    {
      std::cout << "Resource acquired\n";
    }
    ~Resource()
    {
      std::cout << "Resource released\n";
    }
};

class MyClass{
  public:
    Resource resource;
    //No user-defined destructor

};

/*
  认识到析构函数体自身并不直接销毁成员是非常重要的。成员
  是在析构函数体之后隐含的析构阶段中被销毁的

  在整个对象销毁过程中，析构函数体是作为成员销毁步骤之外的另一部分而进行的
*/

struct X{
  X() {std::cout << "x()" << std::endl;}
  X(const X&) {std::cout << "x(const X&)" << std::endl;}
};

void test()
{
  X obj1; //调用普通的构造函数
  X obj2(obj1); //调用拷贝初始化
  std::vector<X> vec1;
  vec1.push_back(obj1);
  auto obj3 = std::make_shared<X>(obj1);
  vec1.push_back(*obj3);
  X* obj4 = new X(obj1);
  vec1.push_back(*obj4);
}

int main()
{
  //MyClass obj;
  test();
  return 0;

}
