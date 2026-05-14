#include <stdio.h>
#include <stdlib.h>

#define N 10
void Swap(int *x, int *y);
void Transpose(int *a, int n);
void InputMatrix(int *a, int n);
void PrintMatrix(int *a, int n);

int main(void) {
  int s[N][N], n;
  scanf("%d", &n);
  InputMatrix(*s, n);
  Transpose(*s, n);
  PrintMatrix(*s, n);
  return 0;
}

void Swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void Transpose(int *a, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      Swap(a + (i * n) + j, a + (j * n) + i);
    }
  }
}

void InputMatrix(int *a, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      fscanf(stdin, "%d", a + (i * n) + j);
    }
  }
}

void PrintMatrix(int *a, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      fprintf(stdout, "%d ", *(a + (i * n) + j));
    }
    printf("\n");
  }
}
