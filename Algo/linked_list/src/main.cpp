#include "../include/DoubleList.hpp"
#include "../include/SeqList.hpp"
#include "../include/SingleList.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

int main() {
  std::cout << "========= 顺序表测试 ==========\n";
  SeqList<int> seq{}; // 大括号初始化栈对象
  seq.insert(0, 10);
  seq.insert(1, 20);
  seq.insert(2, 30);
  seq.print();
  seq.remove(1);     // 删除 20
  seq.update(1, 99); // 将 30 改为 99
  seq.print();

  std::cout << "\n=========== 单链表测试 =============\n";
  SingleList<std::string> slist{}; // 测试泛型 String
  slist.insert(0, "Arch");
  slist.insert(1, "Linux");
  slist.insert(2, "Neovim");
  slist.print();
  slist.remove(1);
  slist.print();

  std::cout << "\n============== 双向链表测试 =============\n";
  DoubleList<double> dlist{}; // 测试泛型Double
  dlist.insert(0, 3.14);
  dlist.insert(1, 2.71);
  dlist.insert(1, 1.618); // 插在中间
  dlist.print();
  dlist.remove(0);
  dlist.print();
  std::cout << dlist.get(1) << "\n";

  return EXIT_SUCCESS;
}
