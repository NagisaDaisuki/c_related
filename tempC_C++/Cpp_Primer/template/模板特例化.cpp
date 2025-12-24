#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <cstring>
/*
    模板特例化
    ---->编写单一模板，使之对任何可能的模板实参都是最适合的，都能实例化
    这并不是总是能办到
    //第一个版本可以比较任意两个类型
    template<typename T> Sales_data compare(const T&, const T&);
    // 第二个版本处理字符串字面常量
    template<size_t N,size_t M>
    Sales_data compare(const char(&)[N],const char(&)[M]);

    当我们传递一个字符串字面常量或一个数组时编译器才会调用接受两个非类型模板参数的版本
    
    
*/

template<typename T> Sales_data compare(const T& t1,const T& t2)
{
  std::cout << "first compare executed" << std::endl;
  return 1;
}

template<size_t N,size_t M> Sales_data compare(const char(&)[N], const char(&)[M])
{
  std::cout << "second compare executed" << std::endl;
  return 1;
}


// 我们无法将一个指针转换为一个数组的引用，因此当参数是p1和p2时，第二个版本的compare
// 是不可行的

/*
  模板特例化---》
    为了处理字符指针(而不是数组)，可以为第一个版本的compare定义一个模板特例化
    (template specialization)版本。一个特例化版本就是模板的一个独立的的定义，在其中
    一个或多个模板参数被指定为特定的类型
*/ 

template<> 
Sales_data compare(const char* const& p1, const char* const &p2)
{
    return strcmp(p1,p2);    
}

/*
  类模板特例化
  ---->除了特例化函数模板，我们还可以特例化类模板
  我们可以为标准可以hash模板定义一个特例化版本

  一个特例化hash类必须定义
  - 一个重载的调用运算符，接受一个容器关键字类型的对象，返回一个size_t 
  - 两个类型成员，result_type 和 argument_type s,分别调用运算符的返回类型
  和参数类型
  - 默认构造函数和拷贝赋值运算符(可以隐式定义)
  ----> 在定义此特例化版本的hash时，必须在原模板定义所在的命名空间中特例化它

*/
class Sales_data{};

 //全特化
// 打开std命名空间，以便特例化std::hash 
namespace std
{
    template<>
    struct hash<Sales_data>
    {
      //用来散列一个无序容器的类型必须要定义下列类型
      typedef size_t result_type;
      typedef Sales_data argument_type;
      
      size_t operator()(const Sales_data& s) const;
      // 使用合成的拷贝控制成员和默认构造函数
    }
    size_t hash<Sales_data>::operator()(const Sales_data& s) const 
    {
      return 1;
    }
}


// 偏特化
// 类模板部分实例化
/* 
    与函数模板不同，类模板的特例化不必为所有模板参数提供实参。
    可以只指定一部分而非所有的参数，或是参数的一部分而非全部特性
  
    ---> 一个类模板的部分特例化(partial specialization)
    本身是一个模板，使用它时用户还必须为那些在特例化版本中未指定

*/

template<class T> struct remove_reference{
  typedef T type;
};

template<class T> struct remove_reference<T&> //左值引用
{
  typedef T type;
};

template<class T> struct remove_reference<T&&> //右值引用
{
    typedef T type;
};

/*
    特例化成员而不是类
    ----> 我们可以只特例化特定成员函数而不是特例化整个模板
*/

int main()
{
  const char* p1 = "hi",*p2 = "mom";
  //compare(p1,p2);
  //compare("hi","mom");
  
  return EXIT_SUCCESS;
}
