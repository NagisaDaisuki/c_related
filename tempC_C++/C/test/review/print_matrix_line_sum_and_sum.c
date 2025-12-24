#include <stdio.h>

#define MAX_COLS 5

void sumMatrixRows(int rows, int (*p)[MAX_COLS]);

int main(void) {
  int rows;
  scanf("%d", &rows);

  int matrix[rows][MAX_COLS];

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < MAX_COLS; j++) {
      scanf("%d", &matrix[i][j]);
    }
  }
  sumMatrixRows(rows, matrix);

  return 0;
}
void sumMatrixRows(int rows, int (*p)[MAX_COLS]) {
  int line_sum, sum;
  line_sum = sum = 0;
  for (int i = 0; i < rows; i++) {
    line_sum = 0;
    for (int j = 0; j < MAX_COLS; j++) {
      line_sum += *(*(p + i) + j);
      sum += *(*(p + i) + j);
    }
    printf("%d\n", line_sum);
  }
  printf("Total sum = %d\n", sum);
}
