#include <chrono>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <queue>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
void printVector(const std::vector<T> &arr, const std::string &title = "") {
  if (!title.empty()) {
    std::cout << title << ": ";
  }

  for (const T &x : arr) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
}

template <typename T, typename Compare = std::less<T>>
void bubbleSort(std::vector<T> &v, Compare comp = Compare()) {
  const size_t n = v.size();
  if (n < 2)
    return;

  for (size_t i = 0; i < n - 1; ++i) {
    bool swapped = false;
    for (size_t j = 0; j < n - 1 - i; ++j) {
      if (comp(v[j + 1], v[j])) {
        std::swap(v[j], v[j + 1]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}

template <typename T, typename Compare = std::less<T>>
void selectionSort(std::vector<T> &v, Compare comp = Compare()) {
  const size_t n = v.size();
  if (n < 2)
    return;

  for (size_t i = 0; i < n - 1; ++i) {
    size_t minIndex = i;
    for (size_t j = i + 1; j < n; ++j) {
      if (comp(v[j], v[minIndex])) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      std::swap(v[i], v[minIndex]);
    }
  }
}

template <typename T, typename Compare = std::less<T>>
void insertionSort(std::vector<T> &v, Compare comp = Compare()) {
  const size_t n = v.size();
  if (n < 2)
    return;

  for (size_t i = 1; i < n; ++i) {
    T key = std::move(v[i]);
    size_t j = i;
    while (j > 0 && comp(key, v[j - 1])) {
      v[j] = std::move(v[j - 1]);
      --j;
    }
    v[j] = key;
  }
}

template <typename T, typename Compare = std::less<T>>
int partitionFunc(std::vector<T> &v, T low, T high, Compare comp = Compare()) {
  T pivot = v[high];
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    if (comp(v[j], pivot)) {
      ++i;
      std::swap(v[i], v[j]);
    }
  }
  std::swap(v[i + 1], v[high]);
  return i + 1;
}

template <typename T, typename Compare = std::less<T>>
void quickSort(std::vector<T> &v, T low, T high, Compare comp = Compare()) {
  if (comp(low, high)) {
    int pivot = partitionFunc(v, low, high);
    quickSort(v, low, pivot - 1, comp);
    quickSort(v, pivot + 1, high, comp);
  }
}

template <typename T> void quickSort(std::vector<T> &v) {
  quickSort(v, 0, (T)v.size() - 1);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(1, 1000);
  std::vector<int> v(20);

  for (auto &elem : v) {
    elem = dist(gen);
  }

  // std::vector<int> v = {
  //     11, 2, 3, 13, 34, 23, 17, 5, 21, 23,
  // };
  std::cout << "Before Sort:";
  printVector(v);
  std::cout << "\n========================================\n";
  std::cout << "\nSelect a sort: \n";
  std::cout << "1. BubbleSort\n";
  std::cout << "2. SelectionSort\n";
  std::cout << "3. InsertionSort\n";
  std::cout << "4. ShellSort\n";
  std::cout << "5. MergeSort\n";
  std::cout << "6. QuickSort\n";
  std::cout << "7. HeapSort\n";
  std::cout << "8. RadixSort\n";
  // std::cout << "9. Sort\n";
  // std::cout << "10. InsertionSort\n";
  std::cout << "\n========================================\n";
  int n = 0;
  std::cin >> n;
  switch (n) {
  case 1:
    bubbleSort(v);
    break;
  case 2:
    selectionSort(v);
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    quickSort(v);
    break;
  case 7:
    break;
  case 8:
    break;
  // case 1:
  //   break;
  default:
    std::cerr << "Incorrect input, Aborted...";
    break;
  }

  std::cout << "After Sort:";
  printVector(v);

  return EXIT_SUCCESS;
}
