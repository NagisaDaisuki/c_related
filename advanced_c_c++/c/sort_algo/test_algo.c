#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INIT_ARR(ARR, SIZE)                                                    \
  do {                                                                         \
    int __i;                                                                   \
    for (__i = 0; __i < (SIZE); __i++) {                                       \
      (ARR)[__i] = rand() % 1000 + 1;                                          \
    }                                                                          \
  } while (0)

#define PRINT_ARR(ARR, SIZE)                                                   \
  do {                                                                         \
    int __i;                                                                   \
    for (__i = 0; __i < (SIZE); __i++) {                                       \
      printf("%d ", (ARR)[__i]);                                               \
    }                                                                          \
    printf("\n");                                                              \
  } while (0)

typedef enum {
  bubble = 0,
  selection,
  insertion,
  shell,
  merge,
  quick,
  heap,
  count,
  bucket,
  radix,
} SortType;

void choose(int arr[], int size);

int main(void) {
  srand(time(NULL));
  int arr[20];
  memset(arr, 0, sizeof(arr));
  INIT_ARR(arr, 20);
  puts("Before Sort:");
  PRINT_ARR(arr, 20);
  choose(arr, 20);
  puts("After Sort:");
  PRINT_ARR(arr, 20);
  return EXIT_SUCCESS;
}
void choose(int arr[], int size) {
  int a;
  puts("=============================================");
  puts("Please input 0-9:    ");
  puts("0 represent bubble   ");
  puts("1 represent selection");
  puts("2 represent insertion");
  puts("3 represent shell    ");
  puts("4 represent merge    ");
  puts("5 represent quick    ");
  puts("6 represent heap     ");
  puts("7 represent counting ");
  puts("8 represent bucket   ");
  puts("9 represent radix    ");
  puts("=============================================");
  if (scanf("%d", &a) != 1) {
    while (getchar() != '\n')
      ;
    return;
  }
  switch (a) {
  case bubble:
    bubbleSort(arr, size);
    break;
  case selection:
    selectionSort(arr, size);
    break;
  case insertion:
    insertionSort(arr, size);
    break;
  case shell:
    shellSort(arr, size);
    break;
  case merge:
    mergeSort(arr, size);
    break;
  case quick:
    quickSort(arr, size);
    break;
  case heap:
    heapSort(arr, size);
    break;
  case count:
    countingSort(arr, size);
    break;
  case bucket:
    bucketSort(arr, size);
    break;
  case radix:
    radixSort(arr, size);
    break;
  default:
    break;
  }
}
