#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <sstream>


/*
  包扩展
    ----> 对于一个参数包，除了获取其大小外,我们能对它做的唯一的事情就是扩展(expand)
    它。当扩展一个包时，我们还要提供用于每个扩展元素的模式(pattern),扩展一个包就是将它
    分解为构成的元素，对每个元素应用模式，获得扩展后的列表，我们通过
    在模式右边放一个省略号来触发扩展操作
    
    扩展中的模式会独立地运用于包中的每个元素

*/

template<typename T> 
std::string debug_rep(const T& t);
template<typename T>
std::string debug_rep(T* p);

std::string debug_rep(const std::string& s);
std::string debug_rep(char* p);
std::string debug_rep(const char* p);

// print any type we don't otherwise
template<typename T>
std::string debug_rep(const T& t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

// print pointers as their pointer value,followed by the object 
template<typename T>
std::string debug_rep(T* p)
{
    std::ostringstream ret;
    ret << "pointer: " << p;

    if(p)
      ret << " " << debug_rep(*p);
    else 
      ret << " null pointer";
    return ret.str();
}

// non-template version 
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

// function to end the recursion and print 
// the last element 
// this function must be declared before the variadic version 
// print is defined 
template<typename T>
std::ostream& print(std::ostream& os, const T& t)
{
    return os << t;
}

// this version of print will be called for all but the last 
// element in the pack 
template<typename T,typename... Args>
std::ostream& print(std::ostream& os,const T& t,const Args&... rest)
{
  // print the first element 
  os << t << ',';

  // recursive call; print the other arguments 
  return print(os,rest...); //packet extension 
}

// call debug_rep on each arguments in the call to print 
template<typename... Args>
std::ostream& errorMsg(std::ostream& os,const Args&... rest)
{
  return print(os,debug_rep(rest)...); //为debug_rep匹配模式
}


/*
  转发参数包
  在新标准下，我们可以组合使用可变参数模板与forward机制来编写函数，实现
  将其实参不变地传递给其他函数

  emplace_back 成员实现是一个可变参数成员模板
  template<class... Args>
  constexpr reference / reference / void emplace_back(Args&&... args);
  


*/



int main()
{
  errorMsg(std::cout,1,2,3,4,9.0f,"sss","alan");
  return 0;
}
