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

void insertionSort(vector<int> &a) {
  int n = a.size();

  for (int i = 1; i < n; ++i) {
    int key = a[i];
    int j = i - 1;

    while (j >= 0 && a[j] > key) {
      a[j + 1] = a[j];
      --j;
    }

    a[j + 1] = key;

    // 每完成一趟插入后输出
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

  insertionSort(a);

  return EXIT_SUCCESS;
}
