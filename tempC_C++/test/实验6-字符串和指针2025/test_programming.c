#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 字符串a下标为偶数的元素由小到大排序

void sort_even_element(void) {
  char a[] = "labchmfye", t;
  int i, j;
  for (i = 0; i < 7; i += 2) {
    for (j = i + 2; j < 9; j++) {
      if (a[i] > a[j]) {
        t = a[i];
        a[i] = a[j];
        a[j] = t;
        j++;
      }
    }
  }
  puts(a);
}

int main(void) {
  sort_even_element();
  return 0;
}
