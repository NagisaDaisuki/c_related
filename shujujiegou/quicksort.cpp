#include <iostream>
#include <random>
#include <utility> // std::swap
#include <vector>

// lomuto 分区法 快排
int partition(std::vector<int> &arr, int lo, int hi) {
  int pivot = arr[hi]; // 1. 取区间末尾元素为基准
  int i = lo - 1;      // 2. i 为小于等于区的右边界

  for (int j = lo; j < hi; ++j) { // 3. j 扫描 [lo, hi - 1]
    if (arr[j] <= pivot) {
      ++i;
      std::swap(arr[j], arr[i]); // 换到小于区末尾
    }
  }

  // 4. 将基准从末尾换到分界线位置 (i + 1)
  std::swap(arr[i + 1], arr[hi]);
  return i + 1; // 返回基准最终所在的下标
}

// 快排主体
void quicksort(std::vector<int> &arr, int lo, int hi) {
  // 递归终止条件：区间只剩 0 或 1 个元素
  if (lo >= hi) {
    return;
  }

  // 分区操作：pivot_index 处的元素已就位
  int p = partition(arr, lo, hi);

  // 5. 递归排左半
  quicksort(arr, lo, p - 1);

  // 6. 递归排右半
  quicksort(arr, p + 1, hi);
}

// 辅助重载函数：方便调用，无需手动传下标
void quicksort(std::vector<int> &arr) {
  if (!arr.empty()) {
    quicksort(arr, 0, static_cast<int>(arr.size() - 1));
  }
}

void print(std::vector<int> &arr) {
  for (auto elem : arr) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main(int argc, char *argv[]) {
  std::vector<int> m;
  std::random_device rd;  // 随机种子源
  std::mt19937 gen(rd()); // mt19937 是最常用的梅森旋转引擎
  // 用 rd() 播种

  // 分布：把引擎输出的原始数映射到你想要的区间/形状
  std::uniform_int_distribution<int> dist(1, 100); // [1,100] 均为整数

  // 生成
  for (int i = 0; i < 10; i++) {
    m.push_back(dist(gen));
  }

  // 排序前
  print(m);

  // 排序后
  quicksort(m);
  print(m);
  return 0;
}
