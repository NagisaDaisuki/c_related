#include <cstdlib>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  // 优化标准 I/O 流的性能
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int m, n;
  // 读取学生人数 (m) 和 科目数 (n)
  if (!(std::cin >> m >> n))
    return 0;

  std::vector<std::vector<int>> matrix(m + 1, std::vector<int>(n + 1, 0));

  // 读取成绩，同时计算行和列的总分
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> matrix[i][j];

      // 累加计算当前学生的总分（存放在当前行的最后一列）
      matrix[i][n] += matrix[i][j];

      // 累加计算当前科目的总分（存放在最后一行对应的列）
      matrix[m][j] += matrix[i][j];

      // 累加所有成绩的总分（右下角）
      matrix[m][n] += matrix[i][j];
    }
  }

  for (const auto &row : matrix) {
    bool first = true;
    for (int val : row) {
      // 判断是否为首个元素，使用制表符分割
      if (!first) {
        std::cout << "\t";
      }
      std::cout << val;
      first = false;
    }
    std::cout << "\n";
  }

  return EXIT_SUCCESS;
}
