#include <iostream>

// 定义通用模板
template<typename T>
class MyTemplate
{
  public:
    void process()
    {
      std::cout << "Generic implementation" << std::endl;
    }
};

// 对模板进行特化，针对int类型的特定实现
template<>
class MyTemplate<int>{
  public:
    void process()
    {
      std::cout << "Specialized implementation for int" << std::endl;
    }
};

int main()
{
  MyTemplate<double> obj1;
  obj1.process();
  MyTemplate<int> obj2;
  obj2.process();

  return 0;
}
