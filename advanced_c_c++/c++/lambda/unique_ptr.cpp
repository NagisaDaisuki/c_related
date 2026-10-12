#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main() {
  // 场景 A：unique_ptr 独占内存资源
  std::unique_ptr<int> ptr = std::make_unique<int>(42);

  // std::unique_ptr<int> ptr2 = ptr; // 这里会报错！内存所有权不能拷贝
  std::unique_ptr<int> ptr2 = std::move(ptr); // 转移内存所有权，ptr变空

  // 场景 B：std::thread 独占线程资源
  std::thread t1([]() { std::cout << "线程运行中\n"; });

  // std::thread t2 = t1; //
  // 线程所有权不能拷贝（否则两个对象都会析构同一个线程）
  std::thread t2 = std::move(t1); // 转移线程所有权，t1 不再代表任何线程

  t2.join(); // 只有 t2负责join
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return 0;
}
