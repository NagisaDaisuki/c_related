#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <queue>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * 说明：
 * 1. 前 7 个属于“比较排序”，写成泛型模板，可支持任意可比较类型。
 * 2. 后 3 个（计数/桶/基数）更适合整数或特定数值类型，因此单独实现。
 * 3. 尽量使用 C++11+ 特性：
 *    - auto
 *    - lambda
 *    - std::function
 *    - std::move
 *    - uniform_int_distribution
 *    - static_assert
 *    - 范围 for
 */

// ========================= 工具函数 =========================

template <typename T>
void printVector(const vector<T> &arr, const string &title = "") {
  if (!title.empty()) {
    cout << title << ": ";
  }
  for (const auto &x : arr) {
    cout << x << ' ';
  }
  cout << endl;
}

template <typename T> bool isSorted(const vector<T> &arr) {
  return std::is_sorted(arr.begin(), arr.end());
}

// ========================= 1. 冒泡排序 =========================
template <typename T, typename Compare = std::less<T>>
void bubbleSort(vector<T> &arr, Compare comp = Compare()) {
  const size_t n = arr.size();
  if (n < 2)
    return;

  for (size_t i = 0; i < n - 1; ++i) {
    bool swapped = false;
    for (size_t j = 0; j < n - 1 - i; ++j) {
      if (comp(arr[j + 1], arr[j])) {
        std::swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}

// ========================= 2. 选择排序 =========================
template <typename T, typename Compare = std::less<T>>
void selectionSort(vector<T> &arr, Compare comp = Compare()) {
  const size_t n = arr.size();
  if (n < 2)
    return;

  for (size_t i = 0; i < n - 1; ++i) {
    size_t best = i;
    for (size_t j = i + 1; j < n; ++j) {
      if (comp(arr[j], arr[best])) {
        best = j;
      }
    }
    if (best != i) {
      std::swap(arr[i], arr[best]);
    }
  }
}

// ========================= 3. 插入排序 =========================

template <typename T, typename Compare = std::less<T>>
void InsertionSort_J_1(vector<T> &arr, Compare comp = Compare()) {}

template <typename T, typename Compare = std::less<T>>
void insertionSort(vector<T> &arr, Compare comp = Compare()) {
  const size_t n = arr.size();
  if (n < 2)
    return;

  for (size_t i = 1; i < n; ++i) {
    T key = std::move(arr[i]);
    size_t j = i;
    while (j > 0 && comp(key, arr[j - 1])) {
      arr[j] = std::move(arr[j - 1]);
      --j;
    }
    arr[j] = std::move(key);
  }
}

// ========================= 4. 希尔排序 =========================
template <typename T, typename Compare = std::less<T>>
void shellSort(vector<T> &arr, Compare comp = Compare()) {
  const size_t n = arr.size();
  if (n < 2)
    return;

  for (size_t gap = n / 2; gap > 0; gap /= 2) {
    for (size_t i = gap; i < n; ++i) {
      T temp = std::move(arr[i]);
      size_t j = i;
      while (j >= gap && comp(temp, arr[j - gap])) {
        arr[j] = std::move(arr[j - gap]);
        j -= gap;
      }
      arr[j] = std::move(temp);
    }
    if (gap == 1)
      break;
  }
}

// ========================= 5. 归并排序 =========================
template <typename T, typename Compare = std::less<T>>
void mergeRange(vector<T> &arr, vector<T> &temp, int left, int mid, int right,
                Compare comp) {
  int i = left;
  int j = mid + 1;
  int k = left;

  while (i <= mid && j <= right) {
    if (!comp(arr[j], arr[i])) {
      temp[k++] = std::move(arr[i++]);
    } else {
      temp[k++] = std::move(arr[j++]);
    }
  }

  while (i <= mid)
    temp[k++] = std::move(arr[i++]);
  while (j <= right)
    temp[k++] = std::move(arr[j++]);

  for (int p = left; p <= right; ++p) {
    arr[p] = std::move(temp[p]);
  }
}

template <typename T, typename Compare = std::less<T>>
void mergeSortImpl(vector<T> &arr, vector<T> &temp, int left, int right,
                   Compare comp) {
  if (left >= right)
    return;
  int mid = left + (right - left) / 2;
  mergeSortImpl(arr, temp, left, mid, comp);
  mergeSortImpl(arr, temp, mid + 1, right, comp);
  mergeRange(arr, temp, left, mid, right, comp);
}

template <typename T, typename Compare = std::less<T>>
void mergeSort(vector<T> &arr, Compare comp = Compare()) {
  if (arr.size() < 2)
    return;
  vector<T> temp(arr.size());
  mergeSortImpl(arr, temp, 0, static_cast<int>(arr.size()) - 1, comp);
}

template <typename T, typename Compare = std::less<T>>
void MergeSortRange(vector<T> &arr, vector<T> &temp, int left, int right,
                    int mid, Compare comp = Compare()) {
  int i = left;    // 左半区当前元素
  int j = mid + 1; // 右半区当前元素
  int t = left;    // 新数组当前元素

  while (i <= mid && j <= right) {
    if (!comp(arr[j], arr[i]))
      temp[t++] = arr[i++];
    else
      temp[t++] = arr[j++];
  }

  while (i <= mid)
    temp[t++] = arr[i++];
  while (j <= right)
    temp[t++] = arr[j++];

  for (int p = left; p < right; p++) {
    arr[p] = temp[p];
  }
}

template <typename T, typename Compare = std::less<T>>
void MergeSortImpl(vector<T> &arr, vector<T> &temp, int left, int right,
                   Compare comp = Compare()) {
  if (left >= right)
    return;

  int mid = left + (right - left) / 2;

  MergeSortImpl(arr, temp, left, mid, comp);
  MergeSortImpl(arr, temp, mid + 1, right, comp);

  MergeSortRange(arr, temp, left, right, mid, comp);
}

template <typename T, typename Compare = std::less<T>>
void MergeSort(vector<T> &arr, Compare comp = Compare()) {
  size_t n = arr.size();
  if (n < 2)
    return;

  vector<T> temp(n);

  MergeSortImpl(arr, temp, 0, static_cast<int>(arr.size()) - 1, comp);
}

// ========================= 6. 快速排序 =========================
template <typename T, typename Compare = std::less<T>>
int partition(vector<T> &arr, int left, int right, Compare comp) {
  T pivot = arr[right];
  int i = left - 1;

  for (int j = left; j < right; ++j) {
    if (!comp(pivot, arr[j])) { // arr[j] <= pivot
      ++i;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[right]);
  return i + 1;
}

template <typename T, typename Compare = std::less<T>>
void quickSortImpl(vector<T> &arr, int left, int right, Compare comp) {
  if (left >= right)
    return;
  int pi = partition(arr, left, right, comp);
  quickSortImpl(arr, left, pi - 1, comp);
  quickSortImpl(arr, pi + 1, right, comp);
}

template <typename T, typename Compare = std::less<T>>
void quickSort(vector<T> &arr, Compare comp = Compare()) {
  if (arr.size() < 2)
    return;
  quickSortImpl(arr, 0, static_cast<int>(arr.size()) - 1, comp);
}

// ========================= 7. 堆排序 =========================
template <typename T, typename Compare = std::less<T>>
void heapify(vector<T> &arr, size_t n, size_t root, Compare comp) {
  size_t largest = root;
  size_t left = 2 * root + 1;
  size_t right = 2 * root + 2;

  // 对于默认 less<T>，这里构建“大根堆”
  if (left < n && comp(arr[largest], arr[left])) {
    largest = left;
  }
  if (right < n && comp(arr[largest], arr[right])) {
    largest = right;
  }

  if (largest != root) {
    std::swap(arr[root], arr[largest]);
    heapify(arr, n, largest, comp);
  }
}

template <typename T, typename Compare = std::less<T>>
void heapSort(vector<T> &arr, Compare comp = Compare()) {
  const size_t n = arr.size();
  if (n < 2)
    return;

  for (int i = static_cast<int>(n / 2) - 1; i >= 0; --i) {
    heapify(arr, n, static_cast<size_t>(i), comp);
  }

  for (int i = static_cast<int>(n) - 1; i > 0; --i) {
    std::swap(arr[0], arr[static_cast<size_t>(i)]);
    heapify(arr, static_cast<size_t>(i), 0, comp);
  }
}

// ========================= 8. 计数排序 =========================
// 适用于非负整数；若有负数，可通过偏移量处理
void countingSort(vector<int> &arr) {
  if (arr.size() < 2)
    return;

  auto [minIt, maxIt] = std::minmax_element(arr.begin(), arr.end());
  int minVal = *minIt;
  int maxVal = *maxIt;

  int range = maxVal - minVal + 1;
  vector<int> count(static_cast<size_t>(range), 0);
  vector<int> output(arr.size());

  for (const auto &x : arr) {
    ++count[x - minVal];
  }

  for (size_t i = 1; i < count.size(); ++i) {
    count[i] += count[i - 1];
  }

  // 倒序遍历保证稳定性
  for (int i = static_cast<int>(arr.size()) - 1; i >= 0; --i) {
    output[--count[arr[static_cast<size_t>(i)] - minVal]] =
        arr[static_cast<size_t>(i)];
  }

  arr = std::move(output);
}

// ========================= 9. 桶排序 =========================
// 这里演示整数桶排序：按区间分桶，桶内用插入排序
void bucketSort(vector<int> &arr, int bucketSize = 5) {
  if (arr.size() < 2)
    return;
  if (bucketSize <= 0)
    bucketSize = 5;

  auto [minIt, maxIt] = std::minmax_element(arr.begin(), arr.end());
  int minVal = *minIt;
  int maxVal = *maxIt;

  int bucketCount = (maxVal - minVal) / bucketSize + 1;
  vector<vector<int>> buckets(static_cast<size_t>(bucketCount));

  for (const auto &x : arr) {
    int index = (x - minVal) / bucketSize;
    buckets[static_cast<size_t>(index)].push_back(x);
  }

  arr.clear();
  for (auto &bucket : buckets) {
    insertionSort(bucket);
    for (const auto &x : bucket) {
      arr.push_back(x);
    }
  }
}

// ========================= 10. 基数排序 =========================
// 这里实现 LSD 基数排序，适用于非负整数
void radixSort(vector<int> &arr) {
  if (arr.size() < 2)
    return;

  auto maxIt = std::max_element(arr.begin(), arr.end());
  int maxVal = *maxIt;

  for (int exp = 1; maxVal / exp > 0; exp *= 10) {
    vector<int> output(arr.size());
    vector<int> count(10, 0);

    for (const auto &x : arr) {
      int digit = (x / exp) % 10;
      ++count[digit];
    }

    for (size_t i = 1; i < count.size(); ++i) {
      count[i] += count[i - 1];
    }

    for (int i = static_cast<int>(arr.size()) - 1; i >= 0; --i) {
      int digit = (arr[static_cast<size_t>(i)] / exp) % 10;
      output[--count[digit]] = arr[static_cast<size_t>(i)];
    }

    arr = std::move(output);
  }
}

// ========================= 测试框架 =========================

template <typename Func>
void runAndPrint(const string &name, const vector<int> &original, Func sorter) {
  vector<int> arr = original;
  sorter(arr);

  cout << std::left << std::setw(12) << name;
  printVector(arr);
  cout << "  是否有序: " << (isSorted(arr) ? "是" : "否") << endl;
  cout << "--------------------------------------------------" << endl;
}

int main() {
  vector<int> data = {53,  3,  542, 748, 14,  214, 154, 63,
                      616, 99, 7,   25,  100, 0,   -5,  42};

  printVector(data, "原始数据");
  cout << "==================================================" << endl;

  runAndPrint("Bubble", data, [](vector<int> &arr) { bubbleSort(arr); });
  runAndPrint("Selection", data, [](vector<int> &arr) { selectionSort(arr); });
  runAndPrint("Insertion", data, [](vector<int> &arr) { insertionSort(arr); });
  runAndPrint("Shell", data, [](vector<int> &arr) { shellSort(arr); });
  runAndPrint("Merge", data, [](vector<int> &arr) { mergeSort(arr); });
  runAndPrint("Quick", data, [](vector<int> &arr) { quickSort(arr); });
  runAndPrint("Heap", data, [](vector<int> &arr) { heapSort(arr); });

  // 计数排序支持负数（这里做了偏移处理）
  runAndPrint("Counting", data, [](vector<int> &arr) { countingSort(arr); });

  // 桶排序这里也支持整数，包括负数
  runAndPrint("Bucket", data, [](vector<int> &arr) { bucketSort(arr, 10); });

  // 基数排序通常只适合非负整数，因此这里单独给一组数据
  vector<int> radixData = {53,  3,  542, 748, 14,  214, 154, 63,
                           616, 99, 7,   25,  100, 0,   42};
  printVector(radixData, "Radix 原始");
  runAndPrint("Radix", radixData, [](vector<int> &arr) { radixSort(arr); });

  cout << endl;

  // 演示自定义比较器：降序排序
  vector<int> descData = {5, 1, 8, 3, 9, 2};
  printVector(descData, "降序测试原始");
  quickSort(descData, std::greater<int>());
  printVector(descData, "QuickSort降序");

  return 0;
}
