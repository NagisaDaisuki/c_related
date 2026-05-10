#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void printArray(const vector<int> &a) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (i)
      cout << " ";
    cout << a[i];
  }
  cout << endl;
}

int partitionFunc(vector<int> &a, int low, int high) {
  int pivot = a[high];
  int i = low - 1;
  for (int j = low; j < high; ++j) {
    if (a[j] <= pivot) {
      ++i;
      swap(a[i], a[j]);
    }
  }
  swap(a[i + 1], a[high]);

  printArray(a); // 每次划分完成后输出
  return i + 1;
}

void quickSortHelper(vector<int> &a, int low, int high) {
  if (low < high) {
    int pi = partitionFunc(a, low, high);
    quickSortHelper(a, low, pi - 1);
    quickSortHelper(a, pi + 1, high);
  }
}

void quickSort(vector<int> &a) { quickSortHelper(a, 0, (int)a.size() - 1); }

int main(void) {
  vector<int> arr = {256, 301, 751, 129, 937, 863, 742, 694, 76, 438};

  quickSort(arr);
  printArray(arr);
  return 0;
}
