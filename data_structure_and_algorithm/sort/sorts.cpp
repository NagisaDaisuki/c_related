#include <algorithm>
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
  cout << '\n';
}

template <typename T> bool isSorted(const vector<T> &arr) {
  return std::is_sorted(arr.begin(), arr.end());
}

// ========================= 1. 冒泡排序 =========================

// 相邻两个元素比较，顺序错了就交换。
//
// 每一趟会把当前未排序区间里的 最大值冒到最后面。

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

// 每一趟从未排序区间里找出 最小值，然后放到前面。

template <typename T, typename Compare = std::less<T>>
void SelectionSort(vector<T> &arr, Compare comp = Compare()) {
  const size_t n = arr.size();
  if (n < 2)
    return;
  for (size_t i = 0; i < n - 1; ++i) {
    size_t best = i;
    for (size_t j = i + 1; j < n; j++) {
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

// 3. 插入排序 Insertion Sort
// 核心思想
//
// 把数组分成两部分：
//
// [已排序区] [未排序区]
//
// 每次从未排序区取出第一个元素，插入到已排序区的正确位置。
//
// 类似打扑克牌整理手牌。

template <typename T, typename Compare = std::less<T>>
void InsertionSort(vector<T> &arr, Compare comp = Compare()) {
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

// 4. 希尔排序 Shell Sort
// 核心思想
//
// 希尔排序是插入排序的改进版。
//
// 插入排序的问题是：元素只能一格一格移动。
//
// 希尔排序先让元素按较大的间隔 gap
// 分组，在每组内部做插入排序，让元素可以“跳跃式移动”。
//
// 最后 gap = 1 时，就是普通插入排序，但此时数组已经接近有序。

template <typename T, typename Compare = std::less<T>>
void ShellSort(vector<T> &arr, Compare comp = Compare()) {
  const size_t n = arr.size();
  if (n < 2)
    return;

  for (size_t gap = n / 2; gap > 0; gap /= 2) {
    for (size_t i = gap; i < n; ++i) {
      T temp = std::move(arr[i]);
      size_t j = i;
      while (j >= gap && comp(temp, arr[j - gap])) {
        arr[j] = arr[j - gap];
        j -= gap;
      }
      arr[j] = std::move(temp);
    }
    if (gap == 1)
      break;
  }
}

// ========================= 5. 归并排序 =========================
// 5. 归并排序 Merge Sort
// 核心思想
//
// 归并排序是典型的 分治法。
//
// 分治就是：
//
// 分：把数组不断拆成左右两半
// 治：分别排序左右两半
// 合：把两个有序数组合并成一个有序数组

// 一句话理解：**先把数组不断二分，直到每个小区间只剩 1 个元素**；
// mergeSortImpl(); 干的事情，不断找 mid划分左右两个子队列
// 然后从小到大，把两个已经有序的小区间合并成一个更大的有序区间。
// mergeRange(); 干的事情，将两个子序列合并

// mergeSort() -> 入口函数，负责创建临时数组 temp
// mergeSortImpl() -> 递归拆分数组
// mergeRange() -> 合并两个已经有序的区间

/*
 *  mergeSort
    -> mergeSortImpl
          -> mergeSortImpl 左半边
          -> mergeSortImpl 右半边
          -> mergeRange 合并左右两边
 * */

/*
 *  假设数组是：
 *  45 32 12 77 48 97 2 36
 *  下标是：
 *  0  1  2  3  4  5  6  7
 *  第一次调用：
 *  mergeSortImpl(arr, temp, 0, 7, comp);
 *  计算：
 *  mid = 0 + (7 - 0) / 2 = 3;
 *  于是分成：
 *  左半边：[0, 3] -> 45 32 12 77
    右半边：[4, 7] -> 48 97 2 36
 *  然后继续递归左半边：
 *  mergeSortImpl(arr, temp, 0, 3, comp);
 *  再分成：
 *  [0, 1] -> 45 32
 *  [2, 3] -> 12 77
 *  再继续：
 *  [0, 0] -> 45
 *  [1, 1] -> 32
 *  当区间只剩一个元素时：
 *  if (left >= right)
 *    return;
 *  因为单个元素天然有序。
 *
 * */

// 拆分结构

/*
 *      [45 32 12 77 48 97 2 36] // mid = 3, depth = 4, 满二叉树
          /                    \
 [45 32 12 77]              [48 97 2 36]
     /       \                /        \
 [45 32]   [12 77]        [48 97]    [2 36]
  /   \      /   \          /   \      /   \
[45] [32] [12] [77]      [48] [97]  [2] [36]
 * */

// 合并时反过来

/*
 * [45] + [32]     -> [32 45]
[12] + [77]     -> [12 77]
[32 45] + [12 77] -> [12 32 45 77]

[48] + [97]     -> [48 97]
[2] + [36]      -> [2 36]
[48 97] + [2 36] -> [2 36 48 97]

[12 32 45 77] + [2 36 48 97]
-> [2 12 32 36 45 48 77 97]
 * */

/*  归并排序的核心：
 *  拆的时候不排序
    合的时候排序
 * */

template <typename T, typename Compare = std::less<T>>
void MergeRange(vector<T> &arr, vector<T> &temp, int left, int mid, int right,
                Compare comp = Compare()) {
  // 函数假设
  // arr[left ... mid] 已经有序
  // arr[mid+1 ... right] 已经有序
  // 它的任务是把这两段合并成：
  // arr[left ... right] 有序

  int i = left;    // 左半区当前元素
  int j = mid + 1; // 右半区当前元素
  int k = left;    // temp当前要放入的位置

  while (i <= mid && j <= right) {
    if (!comp(arr[j], arr[i])) { // (arr[j] >= arr[i])
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
    arr[p] = std::move(temp[p]); // 将 temp数组里的内容移动回 arr
  }
}

template <typename T, typename Compare = std::less<T>>
void MergeSortImpl(vector<T> &arr, vector<T> &temp, int left, int right,
                   Compare comp = Compare()) {
  if (left >= right)
    return; // 排序队列只有一个元素返回

  int mid = left + (right - left) / 2;
  MergeSortImpl(arr, temp, left, mid, comp);
  MergeSortImpl(arr, temp, mid + 1, right, comp);

  MergeRange(arr, temp, left, mid, right, comp);
}

template <typename T, typename Compare = std::less<T>>
void MergeSort(vector<T> &arr, Compare comp = Compare()) {
  if (arr.size() < 2)
    return;
  vector<T> temp(arr.size());
  // 因为归并排序合并两个有序区间时，不能简单原地交换(in-place)。
  //  它需要把较小的元素依次放到临时数组里，再复制回原数组。
  MergeSortImpl(arr, temp, 0, static_cast<int>(arr.size()) - 1, comp);
}

int main(void) {

  vector<int> arr{3, 5, 2, 4, 8, 6, 10, 9};
  cout << "排序前：" << "\n";
  printVector(arr);
  // SelectionSort(arr, [](int a, int b) { return a > b; });
  MergeSort(arr, [](int a, int b) { return a > b; });
  cout << "排序后：" << "\n";
  printVector(arr, "MergeSort");
  return EXIT_SUCCESS;
}
