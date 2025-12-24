#include <stdio.h>
#include <stdlib.h>

typedef struct rectangle {
  int x1, y1, x2, y2;
  float area;
} Rectangle;

void calc_print_rectangle_area();
int compare_rec(const void *rec1, const void *rec2);
#define MALLOC(num, type) (type *)malloc((num) * sizeof(type));

int main(void) {
  calc_print_rectangle_area();
  return 0;
}

int compare_rec(const void *rec1, const void *rec2) {
  const Rectangle *h1 = (const Rectangle *)rec1;
  const Rectangle *h2 = (const Rectangle *)rec2;

  if (h1->area < h2->area)
    return 1;
  if (h1->area > h2->area)
    return -1;
  return 0;
}

void calc_print_rectangle_area() {
  int num = 0;
  float sum_area, avg_area;
  sum_area = avg_area = 0.0;
  if (scanf("%d", &num) != 1 && num > 0)
    return;
  Rectangle *rec = MALLOC(num, Rectangle);
  Rectangle *ptr;
  for (ptr = rec; ptr < rec + num; ptr++) {
    if (scanf("%d %d %d %d", &(*ptr).x1, &(*ptr).y1, &(*ptr).x2, &(*ptr).y2) !=
        4)
      return;
    ptr->area = abs(ptr->x1 - ptr->x2) * abs(ptr->y1 - ptr->y2);
    sum_area += ptr->area;
  }

  qsort(rec, num, sizeof(Rectangle), compare_rec);

  for (ptr = rec; ptr < rec + num; ptr++) {
    printf("%d,%d,%d,%d,area=%.1f\n", ptr->x1, ptr->y1, ptr->x2, ptr->y2,
           ptr->area);
  }

  avg_area = sum_area / num;
  printf("%.1f\n", avg_area);

  free(rec);
}
