#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int arr_size = 0;
  int count = 1;
  if (scanf("%d", &arr_size) != 1) {
    return -1;
  }

  int arr[arr_size];
  memset(arr, 0, sizeof(arr));

  int i;
  for (i = 0; i < arr_size; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      return -1;
    }
  }

  int max = arr[0];

  for (i = 1; i < arr_size; i++) {
    if (arr[i] > arr[i - 1] && max < arr[i]) {
      count++;
      max = arr[i];
    }
  }

  printf("%d\n", count);
  return 0;
}
