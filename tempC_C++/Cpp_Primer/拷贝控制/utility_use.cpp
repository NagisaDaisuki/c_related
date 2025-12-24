#include <iostream>
#include <utility>
#include <string>
#include <vector>

/*
    utility 头文件常用的工具函数和模板
*/

//1.std::pair 用于存储两个元素的有序对
std::pair<int,double> myPair(42，3.14);

//2.std::make_pair 创建一个std::pair 对象
auto myPai1r = std::make_pair(42,3.14);

//3.std::swap 交换两个值
int a = 5,b = 10;
std::swap(a,b);

//4.std::move 将左值转换为右值引用，通常用于实现移动语义
int c = 42;
int&& d = std::move(c);


//5.std::forward 在模板中保持参数的引用类型
template <typename T>
void myFunction(T&& value)
{
  //使用std::forward 来保持参数的引用类型
  //someOtherFunction(std::forward<T>(value));
}

//6.std::tuple 用于存储多个元素的有序集合
std::tuple<int,double,std::string> myTuple(42,3.14,"hello");

//7.std::make_tuple 创建一个'std::tuple'对象
auto myTupl1e = std::make_tuple(42,3.14,"hello");

//8.std::get 获取'std::tuple' 中的元素
std::tuple<int,double,std::string> myTuple2(42,3.14,"hello");
int intValue = std::get<0>(myTuple2); //尖括号中填入访问tuple类型的下标
