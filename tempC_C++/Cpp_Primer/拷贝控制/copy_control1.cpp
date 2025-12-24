#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>


/*
   三/五法则
   当定义一个类时，我们显式或隐式地指定了此类型的对象在拷贝、赋值和销毁时做什么
   一个类通过定义三种特殊的成员函数来控制这些操作：
      拷贝构造函数、拷贝赋值运算符和析构函数
   
   拷贝构造函数定义了当用同类型的另一个对象初始化新对象时做什么，拷贝赋值运算符定义了
   将一个对象赋予同类型的另一个对象时做什么，析构函数定义了此类型的对象销毁时做什么
   我们将这些操作称为拷贝控制操作
    
   "需要析构函数的类也需要拷贝和赋值操作"
      从"需要析构函数"可知，类中必然出现了指针类型的成员(否则不需要我们写析构函数，默认的析构
      函数就够了)，所以，我们需要自己写析构函数来释放给指针所分配的内存来防止内存泄漏

      那么为什么说"也需要拷贝构造函数和赋值操作"呢?原因是: 类中出现了指针类型的成员，必须防止浅拷贝
      问题。所以需要自己书写拷贝构造函数和拷贝赋值运算符，而不能使用默认的拷贝构造函数和默认的拷贝
      赋值运算符

    "需要拷贝操作的类也需要赋值操作，反之亦然"

    "析构函数不能是删除的成员"
      如果析构函数是删除的，那么无法销毁此类型的对象。对于一个删除了析构函数的类型，编译器不允许定义该变量
      或创建该类的临时对象。而且，如果一个类有某个成员的类型删除了析构函数，我们也不能定义该类的变量或临时对象  
*/

/*
  使用=default
    可以通过将拷贝控制成员显式声明=default来要求编译器生成合成的版本
    class Sales_data{
      Sales_data() = default;
      Sales_data(const Sales_data&) = default;
      ~Sales_data() = default;
    };

    Sales_data& Sales_data::operator=(const Sales_data&) = default;
  当我们在类内用=default修饰成员的声明时，合成的函数将隐式声明为内联
  如果不希望合成的成员是内联函数，应该只对成员的类外定义使用=default;

  阻止拷贝
    使用=delete将拷贝函数和拷贝赋值运算符定义为删除的函数来阻止拷贝
  
  
*/ 
struct noCopy
{
    noCopy() = default; //默认构造函数
    noCopy(const noCopy&) = delete; //阻止拷贝
    noCopy& operator=(const noCopy&) = delete; //阻止赋值
};

/*
    与default不用，=delete 必须出现在函数第一次声明的时候
*/

/*
    合成的拷贝构造函数可能是删除的
    本质上，这些规则的含义是：如果一个类有数据成员不能默认构造
    、拷贝、复制或销毁，则对应的构造函数将被定义为删除的
*/

//删除的构造函数
//如果类的析构函数被声明为删除或私有，那么合成的拷贝构造函数也会被删除
class MyClass{
    //删除析构函数
    ~MyClass() = delete;
};

//删除的成员变量的拷贝构造函数被删除
//如果类中的某个成员变量的 拷贝构造函数/拷贝赋值运算符 被删除，那么合成的 拷贝构造函数/拷贝赋值运算符 也会被删除
class NonCopyable
{
  public:
    NonCopyable() = default;
  private:
    //删除的拷贝构造函数
    NonCopyable(const NonCopyable&) = delete;

};
class MyClass
{
  private:
    NonCopyable nonCopyableObj; //成员删除的 拷贝构造函数
};

class Base{
  public:
     //删除的拷贝构造函数
      Base(const Base&) = delete;
};

class Derived : public Base
{
  //合成拷贝构造函数被删除
}；

/*

    private 拷贝控制
      在新标准发布之前，类是通过将其拷贝构造函数和拷贝赋值运算符声明为private来阻止拷贝
    class PrivateCopy
    {
      //无访问说明符；接下来的成员默认为private的；·
      //拷贝控制成员为private的，因此普通用户代码无法访问
      PrivateCopy(const PrivateCopy&);
      PrivateCopy& operator=(const PrivateCopy&);
      //其他成员
      public:
        PrivateCopy() = default;
        ~PrivateCopy(); //用户可以定义此类型的对象，但无法拷贝它们
    };
*/

void use()
{

}

int main()
{
    use();
    return 0;
}
