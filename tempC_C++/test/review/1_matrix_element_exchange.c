#include <stdio.h>

void input_matrix(void);

int main(void) {
  input_matrix();
  return 0;
}

void input_matrix(void) {
  int i, j;
  int n = 0;
  fscanf(stdin, "%d", &n);
  int m[n][n];

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      fscanf(stdin, "%d", &m[i][j]);
    }
  }

  for (i = 0; i < n; i++) {
    int temp = m[i][i];
    m[i][i] = m[i][n - i - 1];
    m[i][n - i - 1] = temp;
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      fprintf(stdout, "%d ", m[i][j]);
    }
    printf("\n");
  }
}
