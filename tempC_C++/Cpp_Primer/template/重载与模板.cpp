#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream> 
/*
  重载与模板
  
  ----> 函数模板可以被另一个模板或者一个普通非模板函数重载。与
  往常一样，名字相同的函数必须具有不同数量或类型的参数
  
  正确定义一组重载的函数模板需要对类型间的关系以及模板函数允许的有限的实参类型
  转换有深刻的理解

  当存在多个同样好的函数模板时，编译器选择最特例化的版本，
  处于相同的原因，一个非模板函数比一个模板函数更好
  

*/

// 编写重载模板

// 接受一个const对象的引用
template<typename T> std::string debug_rep(const T& t)
{
  std::ostringstream ret;
  ret << t; //使用T的输出出运算符打印t的一个表示形式
  return ret.str();
}
// 此函数可以用来生成一对象对应的string表示，该对象可以是任意具备输出运算符的类型

// 打印指针的版本
template<typename T> std::string debug_rep(T* p)
{
  std::ostringstream ret;
  ret << "pointer: " << p; //打印指针本身的值
  if(p)
    ret << " " << debug_rep(*p); //打印p指向的值
  else 
    ret << " null pointer\n"; //或者指出p为空
  return ret.str();
}

// 非函数模板的重载版本(更特例化)
/*
  为了使char* 版本的debug_rep 正常工作，在定义此版本时
  debug_rep(const string&)的声明必须在作用域中
  否则，就可能调用错误的debug_rep版本(未最优匹配到函数版本)

tips: 在定义任何函数之前，记得声明所有重载的函数版本。这样就不必担心编译器
由于未遇到你希望调用的函数而实例化一个并非内所需的版本
*/
std::string debug_rep(const std::string& s)
{
  return '"' + s + '"';
}

std::string debug_rep(char* p)
{
  return debug_rep(std::string(p));
}

std::string debug_rep(const char* p)
{
  return debug_rep(std::string(p));
}



int main()
{

  return 0;
}
