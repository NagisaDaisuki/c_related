#include <stdio.h>

void matrix_mul(void);

int main(void) {
  matrix_mul();
  return 0;
}
void matrix_mul(void) {
  int m, n, p;
  scanf("%d %d %d", &m, &n, &p);
  int matrixA[10][10];
  int matrixB[10][10];
  int matrixC[10][10] = {0};

  int i, j, k;
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &matrixA[i][j]);
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < p; j++) {
      scanf("%d", &matrixB[i][j]);
    }
  }

  for (i = 0; i < m; i++) {
    for (j = 0; j < p; j++) {
      // matrixC[i][j] = 0;
      for (k = 0; k < n; k++) {
        matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
      }
    }
  }

  for (i = 0; i < m; i++) {
    for (j = 0; j < p; j++) {
      printf("%4d", matrixC[i][j]);
    }
    printf("\n");
  }
}
