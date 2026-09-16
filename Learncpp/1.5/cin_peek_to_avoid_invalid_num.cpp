#include <iostream>
#include <limits>

int main() {
  int age{};
  while (true) {
    std::cout << "请输入年龄：";
    std::cin >> age;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "错误！首字符不是数字。\n";
    } else {
      // 提取虽然成功，但我们要查岗：用std::cin.peek()偷看
      // 缓冲区下一个字符
      char nextChar = std::cin.peek();

      // 如果下一个字符不是换行符，说明数字后面跟着乱码(比如 1h29里的 h)
      if (nextChar != '\n' && nextChar != ' ') {
        std::cout << "错误！数字后包含非法字符，请重新输入纯数字。\n";
        // 必须清空剩下的乱码，比如把 h29\n 扔掉
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break; // 通过
      }
    }
  }
  std::cout << "输入成功！年龄为：" << age << '\n';
  return 0;
}
