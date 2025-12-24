
#include <stdio.h>
#include <stdlib.h>
#define N 4

void inputArray(int *p, int m, int n);
void outputArray(int *p, int m, int n);

int main(void) {
  int a[3][4];
  inputArray(*a, 3, 4);
  outputArray(*a, 3, 4);
  return EXIT_SUCCESS;
}

// 形参声明为指向列数已知的二维数组的列指针，输入数组元素值
void inputArray(int *p, int m, int n) {
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &p[i * n + j]);
    }
  }
}
void outputArray(int *p, int m, int n) {
  int i, j;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("%d ", p[i * n + j]);
    }
  }
}
