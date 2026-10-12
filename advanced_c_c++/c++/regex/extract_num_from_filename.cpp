#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> files = {
      "IMG_001.jpg",
      "IMG_002.jpg",
      "photo_123.png",
      "no_number.txt",
  };

  std::regex re(R"((\d+))");

  for (const auto &f : files) {
    std::smatch m;
    if (std::regex_search(f, m, re))
      std::cout << f << " -> 数字：" << m[1] << '\n';
    else
      std::cout << f << " -> 没有数字\n";
  }

  return EXIT_SUCCESS;
}
