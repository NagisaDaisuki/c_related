#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
// 函数模板永远在第一个声明
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

// print pointers as their pointer lue, followed by the object 
// to which the pointer points 
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

// non_template version
std::string debug_rep(const std::string &s)
{
  return '"' + s  + '"';
}

// convert the character pointers to string and call the string version of debug_rep

std::string debug_rep(char* p)
{
  return debug_rep(std::string(p));
}

std::string debug_rep(const char* p)
{
  return debug_rep(std::string(p));
}

// using variadic parameter to write function to
// the end recursion and print the last element
template<typename T>
std::ostream& print(std::ostream& os,const T& t)
{
  return os << t;
}

template<typename T,typename... Args>
std::ostream& print(std::ostream& os,const T& t,const Args&... args)
{
  os << t << ',';
  return print(os,args...);
}

template<typename... Args>
std::ostream& errorMsg(std::ostream& os,const Args... rest)
{
  return print(os,debug_rep(rest)...);
}

int main()
{
  errorMsg(std::cout,1,2,3,4,9.0f,"sss","alan");
  return 0;
}
