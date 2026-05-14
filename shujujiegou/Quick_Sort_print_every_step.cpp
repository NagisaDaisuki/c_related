#include <cstdlib>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

void printArray(const vector<int> &a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i)
      cout << " ";
    cout << a[i];
  }
  cout << "\n";
}

// 子表第一个元素作为枢轴(pivot)
int partition(vector<int> &a, int low, int high) {
  int pivot = a[low];
  while (low < high) {
    while (low < high && a[high] >= pivot) {
      --high;
    }
    a[low] = a[high];

    while (low < high && a[low] <= pivot) {
      ++low;
    }
    a[high] = a[low];
  }
  a[low] = pivot;
  return low;
}

void quick_sort(vector<int> &a, int low, int high) {
  if (low < high) {
    int pivotPos = partition(a, low, high);

    // 每次 partition 后输出整个数组
    printArray(a);
    quick_sort(a, low, pivotPos - 1);
    quick_sort(a, pivotPos + 1, high);
  }
}

int main() {
  int n;
  cin >> n;

  vector<int> a(n); // 构造函数，初始化 n个元素
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  quick_sort(a, 0, n - 1);

  return EXIT_SUCCESS;
}
