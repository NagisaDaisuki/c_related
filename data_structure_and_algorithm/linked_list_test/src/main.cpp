#include "../include/SeqList.hpp"
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
  return EXIT_SUCCESS;
}
