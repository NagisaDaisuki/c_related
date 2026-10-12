#include <ctime>
#include <iostream>
#include <regex>
#include <string>

// 整段完全匹配
void test_regex_match() {
  std::string s = "abc123";
  std::regex re(R"(\w+\d+)"); // 字母数字下划线 + 数字

  if (std::regex_match(s, re)) {
    std::cout << "完全匹配\n";
  } else {
    std::cout << "不匹配\n";
  }

  if (std::regex_match("abc123", std::regex(R"(\w+)"))) {
    std::cout << "完全匹配\n";
  } else {
    std::cout << "不匹配\n";
  }

  if (std::regex_match("abc123", std::regex(R"(\d+)"))) {
    std::cout << "完全匹配\n";
  } else {
    std::cout << "不匹配\n";
  }
}

// 部分匹配即可
void test_regex_search() {
  std::string s = "hello 123 world";
  std::regex re(R"(\d+)");

  if (std::regex_search(s, re)) {
    std::cout << "找到数字\n"; //
  }
}

// 替换匹配部分
void test_regex_replace() {
  std::string s = "I have 2 apples and 3 bananas";
  std::regex re(R"(\d+)");

  std::string result = std::regex_replace(s, re, "N");
  std::cout << result << '\n';
  // result: "I have N apples and N bananas"

  s.replace(0, s.size(), "I have 2 apples and 3 bananas");
  result =
      std::regex_replace(s, re, "N", std::regex_constants::format_first_only);
  std::cout << result << '\n';
  // 只替换第一个数字
}

// 拿到匹配到的内容和分组
// std::smatch 是
// std::match_results<std::string::const_iterator>的别名
void test_smatch() {
  std::string s = "My phone is 13812345678";
  std::regex re;
  try {
    re = (R"((\d{3})(\d{4})(\d{4}))");
  } catch (const std::regex_error &e) {
    std::cerr << "正则错误：" << e.what() << '\n';
  }

  std::smatch m;
  if (std::regex_search(s, m, re)) {
    std::cout << "整体匹配：" << m[0] << "\n"; // 13812345678
    std::cout << "第1组：" << m[1] << "\n";    // 138
    std::cout << "第2组：" << m[2] << "\n";    // 1234
    std::cout << "第3组：" << m[3] << "\n";    // 5678
    std::cout << "匹配位置：" << m.position(0) << "\n";
    std::cout << "匹配长度：" << m.length(0) << "\n";
  }
}

void test_catch_group() {
  // std::regex_replace 的 $1 $2 捕获组
  // $& 表示整个匹配
  std::string s = "2024-01-15";
  std::regex re(R"((\d{4})-(\d{2})-(\d{2}))");

  std::string result = std::regex_replace(s, re, "$3/$2/$1");
  std::cout << result << '\n';
}

/*
 *  标志	作用
std::regex::icase	忽略大小写
std::regex::multiline	^ $ 匹配每行开头结尾
std::regex::dotall	. 也匹配换行
std::regex::extended	使用 POSIX 扩展语法
std::regex::grep	使用 POSIX grep 语法
 * */

void test_ignore_case() {
  std::string s = "Everything i found GREAT was sunFADED.";
  std::string s1 = "GreAt";
  std::regex re(R"(great)");
  // 忽略大小写
  std::regex re1(R"(great)", std::regex::icase);
  // 多个标志用 `|`     multiline -> ^ $ 匹配每行开头结尾
  std::regex re2(R"(great)", std::regex::icase | std::regex::multiline);

  if (std::regex_search(s, re))
    std::cout << "部分匹配成功\n";
  else
    std::cout << "部分匹配失败\n";

  if (std::regex_search(s, re1))
    std::cout << "部分匹配成功\n";
  else
    std::cout << "部分匹配失败\n";

  if (std::regex_match(s, re2))
    std::cout << "部分匹配成功\n";
  else
    std::cout << "部分匹配失败\n";

  if (std::regex_match(s1, re2))
    std::cout << "部分匹配成功\n";
  else
    std::cout << "部分匹配失败\n";
}

int main() {
  // test_regex_match();
  // test_regex_search();
  // test_regex_replace();
  // test_smatch();
  // test_catch_group();
  test_ignore_case();
  return 0;
}
