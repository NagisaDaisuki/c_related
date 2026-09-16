#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

void printArray(const std::vector<int> &a) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (i)
      std::cout << " ";
    std::cout << a[i];
  }
  std::cout << "\n";
}

// void swap(int &a, int &b) {
//   int temp = a;
//   a = b;
//   b = temp;
// }

void bubbleSort(std::vector<int> &a) {
  size_t n = a.size();
  for (size_t i = 0; i < n - 1; i++) {
    bool swapped = false;
    for (size_t j = 0; j < n - i - 1; j++) {
      if (a[j] > a[j + 1]) {
        std::swap(a[j], a[j + 1]);
        swapped = true;
      }
    }
    printArray(a); // 每排序一次输出
    if (!swapped)
      break; // 排序结束
  }
}

int main(void) {
  size_t size = 0;
  if (!(std::cin >> size)) {
    std::cerr << "错误的输入" << "\n";
    return EXIT_FAILURE;
  }
  std::vector<int> vec(size);

  for (size_t i = 0; i < vec.size(); i++) {
    if (!(std::cin >> vec.at(i))) {
      std::cerr << "错误的输入" << "\n";
      return EXIT_FAILURE;
    }
  }

  bubbleSort(vec);

  return EXIT_SUCCESS;
}
