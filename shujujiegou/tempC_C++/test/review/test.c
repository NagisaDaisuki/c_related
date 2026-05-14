#include <stdio.h>

int main() {
  int m, n, p;
  // 根据题目限制 1<=m,n,p<=10，定义足够大的数组
  int A[10][10], B[10][10], C[10][10];
  int i, j, k;

  // 1. 输入 m, n, p
  if (scanf("%d %d %d", &m, &n, &p) != 3) {
    return 1; // 输入错误处理
  }

  // 2. 输入矩阵 A (m行 n列)
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &A[i][j]);
    }
  }

  // 3. 输入矩阵 B (n行 p列)
  for (i = 0; i < n; i++) {
    for (j = 0; j < p; j++) {
      scanf("%d", &B[i][j]);
    }
  }

  // 4. 矩阵乘法计算: C = A * B
  // C 的行数等于 A 的行数 (m)，列数等于 B 的列数 (p)
  for (i = 0; i < m; i++) {   // 遍历 C 的行
    for (j = 0; j < p; j++) { // 遍历 C 的列
      C[i][j] = 0;            // 初始化当前元素为 0
      // 计算点积：A 的第 i 行 与 B 的第 j 列对应元素相乘求和
      for (k = 0; k < n; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  // 5. 输出矩阵 C
  // 要求：每个元素占4个字符宽度 (右对齐)
  for (i = 0; i < m; i++) {
    for (j = 0; j < p; j++) {
      printf("%4d", C[i][j]); // %4d 实现宽度为4的右对齐
    }
    printf("\n"); // 每打印完一行后换行
  }

  return 0;
}
