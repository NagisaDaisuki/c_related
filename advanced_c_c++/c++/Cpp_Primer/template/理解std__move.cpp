#include <iostream>
#include <string>
#include <vector>

/*
  标准库move函数是使用右值引用的模板的一个很好的例子

  我们可以使用move获得一个绑定到左值上的右值引用

  标准库是这样定义move的
  template<typename T>
  typename remove_reference<T>::type&& move(T&& t)
  {
    return static_cast<typename remove_reference<T>::type&&>(t);
  }
  
  从一个左值static_cast 到一个右值引用是允许的
  --->虽然不能隐式地将一个左值转换为右值引用，但我们可以用
  static_cast显式地将一个左值转换为一个右值引用


  转发
  ---->某些函数需要将其一个或者多个实参连同类型不变地转发给其他函数
  在此情况下，我们需要保持被转发实参的所有性质，包括实参类型是否是const的以及
  实参是左值还是右值

  通过将一个函数参数定义为一个指向模板类型参数的右值引用，我们可以保持其对应的
  实参的所有类型信息

  而使用引用参数(无论是左值还是右值)使得我们可以保持const属性
  因为在引用类型中的const是底层的
  如果将函数参数定义为T1&& 和 T2&& ，通过引用折叠就可以
  保持翻转实参的左值右值属性


tips: 如果一个函数参数是指向模板类型参数的右值引用
它对应的实参的const属性和左值，右值属性将得到保存

  在调用中使用std::forward 保持类型信息
  ----> 我们可以使用std::forward<T>的新标准库设施来传递flip2的参数，
  它能保持原始实参的类型,类似move,forward定义在头文件utility中
  与move不同，forward必须通过显式模板实参来调用
  forward 返回该显式实参类型的右值引用，即forward<T>的返回
  类型是T&&


  template<typename Type> intermediary(Type&& arg)
  {
    finalFcn(std::forward<Type>(arg));
  }

// 由于arg是一个模板类型参数的右值引用
// Type将表示传递给arg的实参的所有类型信息


*/
template<typename F,typename T1,typename T2>
void filp2(F f,T1&& t1,T2&& t2)
{
  f(t2,t1);
}

// 使用forward可再次重写反转函数
template<typename F,typename T1, typename T2>
void filp2(F f,T1&& t1,T2&& t2)
{
    f(std::forward<T2>(t2),std::forward<T1>(t1)); //保持filp2传入实参时的类型
}

void f(int v1,int& v2)
{
    std::cout << v1 << " " << ++v2 << std::endl; 
}

int main()
{
  int j = 10;
  filp2(f,j,42);
  std::cout << j << std::endl;
  return 0;
}
