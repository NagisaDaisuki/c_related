#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

/**
 * @brief 生成并输出 n x n 的螺旋矩阵。
 */
int main() {
  int n;
  int matrix[MAX_SIZE][MAX_SIZE];

  // 1. 读取矩阵的阶数 n
  if (scanf("%d", &n) != 1) {
    fprintf(stderr, "错误：无法读取矩阵阶数 n。\n");
    return EXIT_FAILURE;
  }

  // 检查 n 的合法性
  if (n <= 0 || n > MAX_SIZE) {
    fprintf(stderr, "错误：阶数 n=%d 超出范围 (1-%d)。\n", n, MAX_SIZE);
    return EXIT_FAILURE;
  }

  // 2. 螺旋矩阵填充逻辑

  // 初始化边界和起始值
  int count = 1; // 从 1 开始填充
  int total_elements = n * n;

  // 边界定义：top, bottom, left, right
  int top = 0, bottom = n - 1;
  int left = 0, right = n - 1;

  while (count <= total_elements) {
    // 1. 从左到右 (Top row)
    if (top <= bottom) {
      for (int j = left; j <= right; j++) {
        matrix[top][j] = count++;
      }
      top++; // 顶部边界向下收缩
    }

    // 2. 从上到下 (Right column)
    if (left <= right) {
      for (int i = top; i <= bottom; i++) {
        matrix[i][right] = count++;
      }
      right--; // 右侧边界向左收缩
    }

    // 3. 从右到左 (Bottom row)
    if (top <= bottom) {
      for (int j = right; j >= left; j--) {
        matrix[bottom][j] = count++;
      }
      bottom--; // 底部边界向上收缩
    }

    // 4. 从下到上 (Left column)
    if (left <= right) {
      for (int i = bottom; i >= top; i--) {
        matrix[i][left] = count++;
      }
      left++; // 左侧边界向右收缩
    }
  }

  // 3. 输出 n x n 的螺旋矩阵
  // 要求：每个数字占 4 个字符位置，右对齐。
  printf("\n【样例输出】\n"); // 增加提示信息，匹配样例格式

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // 使用 %4d 实现右对齐，占 4 个字符位置
      printf("%4d", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}
