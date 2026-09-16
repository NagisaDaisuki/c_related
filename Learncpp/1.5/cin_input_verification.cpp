#include <iostream>
#include <limits>

int main() {
  int age{};

  while (true) {
    std::cout << "请输入年龄(必须是纯数字): ";
    std::cin >> age;

    // 检查刚才的输入是否引发了类型错误
    if (std::cin.fail()) {
      std::cin.clear(); // 1. 解除死锁
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // 2. 清空乱码
      std::cout << "错误：你输入的内容包含非数字字符，请重试！\n";
    } else {
      // 提取成功！但为了防止用户输入类似 "18 abc" 这样半对半错的内容
      // 成功后还是使用std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
      // "\n")清理剩余缓冲区内容

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break; // 退出循环
    }
  }

  std::cout << "输入成功！年龄为：" << age << std::endl; // 刷新缓冲区 并换行

  return 0;
}
