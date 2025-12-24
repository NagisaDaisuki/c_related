#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>

class Sales_data{};

// 类型模板参数
template <typename T>
int compare(const T& lhs,const T& rhs)
{
  if(lhs < rhs) return -1; 
  if(rhs < lhs) return 1;
  return 0;
}

// 非类型模板参数

// 一个非类型参数表示一个值而非一个类型
// 当一个模板被实例化的时候，非类型参数被一个用户提供的或编译器推断出的值
// 所替代
// 这些值必须是常量表达式

template <unsigned N, unsigned M>
int comapre(const char (&p1)[N],const char (&p2)[M])
{
  return strcmp(p1,p2);
}


// 编写类型无关的代码
/*
    编写泛型代码的两个重要原则：
      1.模板中的函数参数是const的引用
      2.函数体中的条件判断仅使用<比较运算
    通过将函数参数设定为const的引用，保证函数可以用于不能拷贝的类型

*/

template <typename T> int compare1(const T& v1,const T& v2)
{
    if(std::less<T>()(v1,v2)) return -1;
    if(std::less<T>()(v2,v1)) return 1;
    return 0;
}
// 模板程序应该尽量减少对实参类型的要求

/*
  实例化定义：
  When the compiler instantiates a template, it craetes a new "instance" of
  the template using the actual template arguments in place of the corresponding 
  template parameters
*/
int main()
{
    //Test compare function
    std::cout << compare(1,0) << std::endl;
    //函数模板隐式指定模板实参
    std::vector<int> vec1{1,2,3},vec2{4,5,6};
    std::cout << compare(vec1,vec2) << std::endl;

    return 0;
}

// inline 和 constexpr 的函数模板
template <typename T> inline T min(const T&,const T&);


