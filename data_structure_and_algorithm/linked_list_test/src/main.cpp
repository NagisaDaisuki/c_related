#include "../include/SeqList.hpp"
#include "../include/SingleList.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

int main(void) {

  std::cout << "=========== 顺序链表 ===============\n";
  SeqList<std::string> StringList{};
  std::cout << "插入字面量const char* \n";
  StringList.insert(0, "Hello World!");
  StringList.print();
  std::cout << "插入String \n";
  std::string seq = {'n', 'i', 'h', 'a', 'o'};
  StringList.insert(1, seq);
  StringList.print();
  const char *str = "Will they one day reach their destination?";
  std::cout << "插入const char* \n";
  StringList.insert(2, str);
  StringList.print();
  std::cout << "删除第一个元素\n";
  StringList.remove(1);
  StringList.print();

  std::cout << "============= 单链表 ==================\n";
  SingleList<double> doubleList{1.1, 3.2, 5.4, 1.54, 3.39, 6.28};
  std::cout << "打印 使用initializer_list 初始化的 单链表：\n";
  doubleList.print();
  std::cout << "输入一个不大于" << doubleList.size() << "的插入位置并插入值\n";
  double val1 = 0.0;
  int index = 0;
  if (std::cin >> index && std::cin >> val1 && index <= doubleList.size()) {
    doubleList.insert(index, val1);
  }
  std::cout << "插入后的链表：\n";
  doubleList.print();
  std::cout << "更新链表内元素,先位置后元素：\n";
  if (std::cin >> index && std::cin >> val1 && index < doubleList.size()) {
    doubleList.update(index, val1);
  }
  std::cout << "更新后的链表：\n";
  doubleList.print();

  std::cout << "移除链表中指定位置元素：\n";
  if (std::cin >> index && index < doubleList.size()) {
    doubleList.remove(index);
  }
  std::cout << "移除后的链表：\n";
  doubleList.print();

  return EXIT_SUCCESS;
}
