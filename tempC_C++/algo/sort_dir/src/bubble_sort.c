#include "sort.h"

void bubble_sort(int arr[], int n) {
  int i, j;

  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        SWAP(&arr[j], &arr[j + 1], int);
      }
    }
  }
}