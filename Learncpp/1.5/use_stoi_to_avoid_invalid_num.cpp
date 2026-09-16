/*
 *方案二：字符串整行读取 + 转换（工业界防弹写法）
在现代 C++
工程（甚至你提到的后端开发）中，处理控制台或网络文本输入时，最安全的做法是彻底抛弃
cin >> int。我们将整行作为字符串读取，然后利用 std::stoi（String to
Integer）的报错机制进行正则级别的校验。
 * */

#include <iostream>
#include <string>

int main() {

  // before c++11
  // std::string input = "123";
  // int age;
  // std::stringstream ss(input);
  // ss >> age; // 语法安全但是啰嗦，运行速度慢
  std::string input{};
  int age{};

  while (true) {
    std::cout << "请输入年龄: ";
    std::getline(std::cin, input); // 把整行拿过来

    try {
      size_t pos = 0;
      age = std::stoi(input, &pos); // 尝试把字符串转为整数

      // pos 会记录转换停止的位置
      // 如果 input 是 "123", pos 会走到字符串末尾
      // 如果 input 是 "1h29", pos 会停在字母 'h' 的索引位置(1)。
      if (pos != input.length()) {
        std::cout << "错误：输入中夹杂了非数字字符！\n";
      } else {
        break; // 转换成功且无多余字符
      }
    } catch (const std::invalid_argument &) {
      std::cout << "错误：压根没有输入数字！\n";
    } catch (const std::out_of_range &) {
      std::cout << "错误：超出 int 整数范围\n";
    }
  }

  std::cout << "输入成功！年龄为：" << age << '\n';
  return 0;
}
