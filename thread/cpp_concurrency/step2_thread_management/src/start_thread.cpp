#include "condi.h"
#include <iostream>
#include <thread>
// #include <chrono>
// #include <stdexcept>

int main() {
  // background_task f(114514);
  std::thread my_thread{background_task(114514)};
  // lambda本质上是编译器自动生成了一个带有 operator() 的
  // 匿名类(闭包类型)
  std::thread lambda_thread([]() {
    std::cout << "do_something_else" << '\n';
    std::cout << "do_something" << '\n';
  });
  // 通过捕获列表具备"携带状态"的能力
  int local_var = 42;
  // 捕获 local_var 相当于类中的成员变量
  std::thread lambda_t([local_var]() { std::cout << local_var << std::endl; });
  my_thread.join();
  lambda_thread.join();
  lambda_t.detach(); // 不等待线程,线程的函数可能还在主函数结束退出后运行

  oops();
  try {
    f();
  } catch (const std::exception &e) {
    std::cerr << "[main] 捕获到 f() 抛出的异常：" << e.what() << std::endl;
    // 在这里决定程序接下来该怎么办，比如退出、重试等
  }
  f_detach();
  tv_test(114514);
  std::cout << "程序安全退出" << std::endl;
  return 0;
}
