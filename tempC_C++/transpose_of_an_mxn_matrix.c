#include <stdio.h>
#include <stdlib.h>

// 定义最大行列数，防止缓冲区溢出
#define MAX_SIZE 100

/*
 *  @brief 读取 m x n 矩阵并计算其转置矩阵，然后输出。
 *  原始矩阵 A[i][j] 的元素， 在转置矩阵 B 中位于 B[j][i]。
 *  读入 A[i][j]时，直接将其存储转置矩阵 T[j][i] 中。
 * */

int main(void) {
  int m, n;
  int matrix_T[MAX_SIZE][MAX_SIZE]; // 存储转置矩阵 T，大小为 n x m

  // 1. 读取矩阵的 行数 m 和 列数 n
  if (scanf("%d %d", &m, &n) != 2) {
    // 错误处理：如果无法读取 m 和 n
    fprintf(stderr, "error: failed to read matrix's row and column.\n");
    return EXIT_FAILURE;
  }

  // 检查行列数的合法性质，防止越界
  if (m <= 0 || n <= 0 || m > MAX_SIZE || n > MAX_SIZE) {
    fprintf(stderr, "错误：矩阵行列数 m=%d, n=%d 超出范围 (1-%d)。\n", m, n,
            MAX_SIZE);
    return EXIT_FAILURE;
  }

  // 2. 循环读取 m x n 矩阵的元素，并将其存入转置矩阵 T
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      int element;
      if (scanf("%d", &element) != 1) {
        fprintf(stderr, "错误：读取元素失败，位置 (%d, %d)。\n", i + 1, j + 1);
        return EXIT_FAILURE;
      }

      // 核心转置操作：原矩阵 A[i][j] 存入转置矩阵 T[j][i]
      matrix_T[j][i] = element;
    }
  }

  // 3. 输出 n x m 的转置矩阵
  // 转置矩阵 有 n 行 和 m 列
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      // 输出 当前元素
      printf("%d", matrix_T[i][j]);

      // 确保除最后一个元素外，后面都有空格
      if (j < m - 1)
        printf(" ");
    }
    // 每行结束后输出换行符
    printf("\n");
  }

  return 0;
}
