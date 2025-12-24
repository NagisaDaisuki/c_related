#include <stdio.h>

int main(void) {
  int i, j, a[6];
  int *p[3];
  for (i = 0; i < 6; i++) {
    scanf("%d", &a[i]);
  }
  for (i = 0; i < 3; i++)
    p[i] = &a[2 * i];
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      printf("%4d ", *(*(p + i) + j));
    }
    printf("\n");
  }
  return 0;
}
