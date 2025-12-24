#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <vector>

// 打印vector 到流的辅助函数
template<class Os,class T>
Os& operator<<(Os& os,std::vector<T> const& v)
{
  os << '{';
  for(auto i{v.size()}; const T& e : v)
      os << e << (--i ? "," : "");
  return os << '}';
}


template<class T>
void print_single(T const& v)
{
  if constexpr (std::is_same_v<T,std::decay_t<std::string>>)
    std::cout << std::quoted(v);
  else if constexpr (std::is_same_v<std::decay_t<T>,char>)
    std::cout << "'" << v << "'";
  else 
    std::cout << v;
}

// 打印任意大小元组的辅助函数
template<class Tuple,std::size_t N>
struct TuplePrinter
{
  static void print(const Tuple& t)
  {
    TuplePrinter<Tuple,N - 1>::print(t); //递归
    std::cout << ",";
    print_single(std::get<N - 1>(t));
  }
};

template<class Tuple>
struct TuplePrinter<Tuple,1>
{
  static void print(const Tuple& t)
  {
    print_single(std::get<0>(t)); 
  }
};

template<class... Args>
void print(std::string_view message,const std::tuple<Args...>& t)
{
  std::cout << message << "(";
  TuplePrinter<decltype(t),sizeof...(Args)>::print(t);
  std::cout << ")\n";
}

// 辅助函数结束
int main()
{
  std::tuple<int,std::string,double> t1;
  print("值初始化,t1: ",t1);

  std::tuple<int,std::string,double> t2{42,"Test",-3.14};
  print("通过值进行初始化,t2: ",t2);
  
  std::tuple<char,std::string,double> t3{t2}; 
  print("隐式转换,t3:",t3);

  std::tuple<int,double> t4{std::make_pair(42,3.14)};
  print("从pair构造,t4:",t4);

  // 给定拥有单实参构造函数的分配器 my_alloc my_alloc(int)
  // 用my_alloc(1) 在vector 中分配5 个 int
  using my_alloc = std::allocator<int>;
  std::vector<int,my_alloc> v{5,1,my_alloc{}};

  // 用my_alloc(2) 在tuple中的vector中分配5 个int
  std::tuple<int,std::vector<int,my_alloc>,double> t5
    {std::allocator_arg,my_alloc{},42,v,-3.14};
  print("带分配器构造,t5:",t5);

  return 0;
}


