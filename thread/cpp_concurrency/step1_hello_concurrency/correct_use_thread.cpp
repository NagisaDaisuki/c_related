#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

void hello() {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "子线程执行完毕" << std::endl;
}

int main() {
  std::function<void()> func = hello;
  std::thread t(func);
  std::cout << "主线程等待子线程...\n";
  t.join(); // 阻塞主线程,直到 hello 执行完
  std::cout << "主线程结束" << std::endl;
  return 0;
}