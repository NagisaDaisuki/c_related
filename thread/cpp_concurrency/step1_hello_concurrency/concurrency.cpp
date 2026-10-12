#include <iostream>
#include <string>
#include <thread> // C++11 线程库

void hello() { std::cout << "Hello Concurrent World!\n"; }

void (*current_func)() = hello;

int main() {
  std::thread t(current_func); // 新线程启动
  // 在 std::thread 对象的构造函数中指定 current_func指向的
  // hello函数作为其执行函数
  std::string str = "Nice to see you!";
  std::cout << str << std::endl;
  t.join(); // 等待 std::thread 对象创建的线程
  return 0;
}