#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// #define MY_SORT 0
#define MY_SORT_1 1

template <typename T>
void printArray(const std::vector<T> &arr, std::string title = "") {
  const size_t n = arr.size();

  if (!title.empty()) {
    std::cout << title << ": ";
  }

  for (size_t i = 0; i < n; i++) {
    std::cout << arr[i] << "\t";
  }
  std::cout << "\n";
}

class Test {
private:
  static std::string title;

public:
  void Test1() {
    std::vector<std::string> stringArr = {"Everything", "I",   "Found",
                                          "Great",      "Was", "Sunfaded"};

    printArray(stringArr, "排序前");
#ifdef MY_SORT
    std::sort(stringArr.begin(), stringArr.end(),
              [](const std::string &a, const std::string &b) {
                return a < b;
              }); // 按字典序升序
    std::sort(stringArr.begin(), stringArr.end(),
              [](const std::string &a, const std::string &b) {
                return a.size() < b.size();
              }); // 按字符串长度升序

    std::sort(stringArr.begin(), stringArr.end(),
              [](const std::string &a, const std::string &b) {
                if (a.size() != b.size())
                  return a.size() > b.size();
                return a < b;
              }); // 按长度降序，长度相同按字典序升序
#elif MY_SORT_1
    // 忽略大小写的字典序升序
    std::sort(stringArr.begin(), stringArr.end(),
              [](const std::string a, const std::string b) {
                for (auto &c : a)
                  std::tolower(c);
                for (auto &c : b)
                  std::tolower(c);
                return a < b;
              });
    printArray(stringArr, "排序后");

#endif
  }
};

int main(int argc, char *argv[]) {
  Test t;
  t.Test1();
  return EXIT_SUCCESS;
}
