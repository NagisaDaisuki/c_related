#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

void printArray(const vector<int> &a) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (i)
      cout << " ";
    cout << a[i];
  }
  cout << "\n";
}

void selectionSort(vector<int> &a) {
  int n = a.size();

  for (int i = 0; i < n - 1; ++i) {
    int minIndex = i;

    // 在未排序区间 [i, n - 1] 中找最小值
    for (int j = i + 1; j < n; ++j) {
      if (a[j] < a[minIndex]) {
        minIndex = j;
      }
    }

    // 把最小值交换到当前位置
    swap(a[i], a[minIndex]);

    // 每完成一趟选择后输出
    printArray(a);
  }
}

int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  selectionSort(a);

  return EXIT_SUCCESS;
}
