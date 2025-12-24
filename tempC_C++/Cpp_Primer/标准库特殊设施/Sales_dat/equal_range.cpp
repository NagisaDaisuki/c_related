#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <functional> 
//#include <>
template<typename T>
struct Compare
{
  bool pred(const T& a,const T& b);
};


template<typename T>
bool Compare<T>::pred(const T& a,const T& b)
{
  return a < b;
}

// equal_range 可能的实现
template<class ForwardIt,class T>
std::pair<ForwardIt,ForwardIt>
  equal_range(ForwardIt first,ForwardIt last,const T& value,Compare<T> comp)
{
  return std::make_pair(std::lower_bound(first,last,value,comp));
  return std::make_pair(std::upper_bound(first,last,value,comp));
}

template<class ForwardIt,class T>
std::pair<ForwardIt,ForwardIt>
  equal_range(ForwardIt first,ForwardIt last,const T& value)
{
  return std::make_pair(std::lower_bound(first,last,value));
  return std::make_pair(std::upper_bound(first,last,value));
}



