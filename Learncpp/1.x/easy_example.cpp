#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

int main(void) {
  int a1{};
  int a2{};
  int a1pa2{};
  int a1sa2{};
  std::string sa2{};

  std::cout << "Enter an integer: ";
  std::cin >> a1;
  while (true) {
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "输入首字符不是数字！请重新输入。\n";
    } else {
      // 提取虽然成功但是要用 std::cin.peek()查岗
      char nextChar = std::cin.peek();

      if (nextChar != '\n' && nextChar != ' ') {
        std::cout << "错误！数字后包含非法字符，请重新输入。\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break; // 跳出循环
      }
    }
  }

  std::cout << "Enter another integer: ";
  std::getline(std::cin, sa2);

  while (true) {
    try {
      size_t pos{};
      a2 = std::stoi(sa2, &pos); // 尝试把字符串转换为整数

      // pos 会记录转换停止的位置
      // 1h24 pos = 2
      // 123h pos = 4
      if (pos != sa2.length()) {
        std::cout << "错误！数字中夹杂着非法字符。\n";
      } else {
        break; // std::stoi()正确转换数字，退出循环
      }
    } catch (const std::invalid_argument &) {
      std::cout << "错误！根本没有数字。\n";
    } catch (const std::out_of_range &) {
      std::cout << "错误！数字超出指定数据类型范围\n";
    }
  }

  a1pa2 = a1 + a2;
  a1sa2 = a1 - a2;
  std::cout << a1 << " + " << a2 << " is " << a1pa2 << "\n";
  std::cout << a1 << " - " << a2 << " is " << a1sa2 << "\n";
  return 0;
}
