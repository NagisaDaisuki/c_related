#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <cstdio>
/*
  可变参数模板
  ---> 一个可变参数模板(variadic template)
  就是一个接受可变数目参数的模板函数或模板类，可变数目的参数被称为参数包(parameter packet)
  存在两种参数包：模板参数包(template parameter packet) 表示0个或多个模板参数
  函数参数包(function parameter packet) 表示0个或多个函数参数
  

  使用一个省略号来指出一个模板参数或函数参数表示一个包
  在一个模板参数列表中,class... 或 typename... 指出接下来的
  参数表示0个或多个类型的列表

  在函数参数列表中，如果一个参数的类型是一个模板参数包，
  则此参数也是一个函数参数包

  // Args是一个模板参数包，rest是一个函数参数包
  template<typename T,typename... Args>
  void foo(const T &t,const Args& ... rest);

  
  sizeof...()运算符

  当我们需要知道包中有多少元素时，可以使用sizeof...运算符
  sizeof...返回一个常量表达式
  
  template<typename... Args> void g(Args... args)
  {
    std::cout << sizeof...(Args) << std::endl;
    std::cout << sizeof...(args) << std::endl;
  }
*/

template<typename... Args>
void g(Args... args)
{
    std::cout << sizeof...(Args) << std::endl;
    std::cout << sizeof...(args) << std::endl;
}

// 编写可变参数函数的模板

template<typename T>
std::ostream& print(std::ostream& os,const T& t)
{
  return os << t; //包中最后一个元素之后不打印分割符
}

// 包中除了最后一个元素之外的其他元素都会调用这个版本的print
template<typename T,typename... Args>
std::ostream& print(std::ostream& os,const T& t,const Args&... rest)
{
  os << t << ',';
  return print(os,rest...);
}

int main()
{
 /* g(1,2,"3.14",0.5);
  g(1,3,4);
  g("hello","world");
  g(0.3);
*/
  
  print(std::cout,1,2,3,4,5,6,7,8);
  std::printf("\n");
  print(std::cout,"hello","world");
  
  
  return EXIT_SUCCESS;
}
