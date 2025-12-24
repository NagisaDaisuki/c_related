#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int arr_size = 0;
  int count = 0;
  float sum_5 = 0;
  int i;
  int starter = 2;
  if (fscanf(stdin, "%d", &arr_size) != 1 || arr_size % 5 != 0) {
    perror("input error\n");
    return EXIT_FAILURE;
  }
#ifndef ARR_SIZE
#define ARR_SIZE arr_size
#endif
  int arr[ARR_SIZE] = {};
  for (i = 0; i < arr_size; i++) {
    count++;
    sum_5 += starter;
    arr[i] = starter;
    starter += 2;
    if (count % 5 == 0) {
      printf("%.2f ", sum_5 * 1.0 / 5);
      sum_5 = 0;
    }
  }
  return 0;
}
