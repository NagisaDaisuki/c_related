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

void shellSort(vector<int> &a, const vector<int> &gaps) {
  int m = a.size();

  for (int gap : gaps) {
    // 对每个 gap 做一趟分组插入排序
    for (int i = gap; i < m; ++i) {
      int temp = a[i];
      int j = i - gap;

      while (j >= 0 && a[j] > temp) {
        a[j + gap] = a[j];
        j -= gap;
      }

      a[j + gap] = temp;
    }

    // 每完成一个增量的一趟排序后输出
    printArray(a);
  }
}

int main() {
  int m, n;
  cin >> m >> n;

  vector<int> a(m);
  for (int i = 0; i < m; ++i) {
    cin >> a[i];
  }

  vector<int> gaps(n);
  for (int i = 0; i < n; ++i) {
    cin >> gaps[i];
  }

  shellSort(a, gaps);

  return EXIT_SUCCESS;
}
