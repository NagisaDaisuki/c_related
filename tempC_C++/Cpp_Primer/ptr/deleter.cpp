#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>
/*
  std::unique_ptr提供了删除器(deleter)的功能，通过指定删除器，可以
  自定义std::unique_ptr管理的资源被释放时所执行的操作
*/

//1.使用lambda表达式作为删除器
void lam()
{
  std::unique_ptr<int,std::function<void(int*)>> customPtr(new int(42),
      [](int* ptr){
        std::cout << "Deleting integer with value: " << *ptr << std::endl;
        delete ptr;
      });

  //使用unique_ptr，当unique_ptr被销毁时，lambda表达式会输出被释放的整数的值

}

//2.使用自定义函数作为删除器
void customDeleter(int* ptr)
{
  std::cout << "Deleting integer with value: " << *ptr << std::endl;
  delete ptr;
}

void custom()
{
  std::unique_ptr<int,decltype(&customDeleter)>/* decltype(customDeleter)* */ \
    customPtr(new int(),customDeleter);

}

//3.使用std::default_delete

int main()
{
  std::unique_ptr<int,std::default_delete<int>> defaultDeletePtr(new int());
  return 0;
}
