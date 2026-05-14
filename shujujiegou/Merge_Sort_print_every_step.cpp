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

void mergeArray(vector<int> &a, int left, int mid, int right) {
  vector<int> temp;
  int i = left;
  int j = mid + 1;

  while (i <= mid && j <= right) {
    if (a[i] <= a[j]) {
      temp.push_back(a[i++]);
    } else {
      temp.push_back(a[j++]);
    }
  }

  while (i <= mid) {
    temp.push_back(a[i++]);
  }

  while (j <= right) {
    temp.push_back(a[j++]);
  }

  for (int k = 0; k < (int)temp.size(); ++k) {
    a[left + k] = temp[k];
  }

  // 每完成一次归并，输出整个数组
  printArray(a);
}

void mergeSort(vector<int> &a, int left, int right) {
  if (left >= right)
    return;

  int mid = left + (right - left) / 2;

  mergeSort(a, left, mid);
  mergeSort(a, mid + 1, right);

  mergeArray(a, left, mid, right);
}

int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  mergeSort(a, 0, n - 1);

  return EXIT_SUCCESS;
}
