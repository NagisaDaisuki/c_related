#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x;
  int y;
} POINT;

int main(void) {
  int point_num = 0;
  double area = 0.0;

  if (scanf("%d", &point_num) != 1 || point_num < 2) {
    return -1;
  }
  POINT point_arr[point_num];

  int i;
  for (i = 0; i < point_num; i++) {
    if (scanf("%d %d", &point_arr[i].x, &point_arr[i].y) != 2)
      continue;
  }

  for (i = 1; i < point_num; i++) {
    double height = (double)(point_arr[i].x - point_arr[i - 1].x);
    double sum_of_bases = (double)(point_arr[i - 1].y + point_arr[i].y);
    area += sum_of_bases * height / 2.0;

    // area += (point_arr[i - 1].y + point_arr[i].y) *
    //         (double)(point_arr[i].x - point_arr[i - 1].x) / 2.0;
  }

  printf("%.2lf\n", area);
  return 0;
}
