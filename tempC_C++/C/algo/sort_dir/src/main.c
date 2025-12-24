#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 10

// Macro to print the array
#define ARR_PRINT(ARR, SIZE)                                                   \
  do {                                                                         \
    int __i;                                                                   \
    printf("Array: ");                                                         \
    for (__i = 0; __i < (SIZE); __i++) {                                       \
      printf("%4d", (ARR)[__i]);                                               \
    }                                                                          \
    printf("\n");                                                              \
  } while (0)

int main(void) {
  srand((unsigned)time(NULL));

  int arr[ARR_SIZE] = {};
  int i;
  for (i = 0; i < ARR_SIZE; i++)
    arr[i] = rand() % 100;

  fprintf(stdout, "before bubble sort...\n");
  ARR_PRINT(arr, ARR_SIZE);

  // Call the sorting function from the interface
  // selection_sort(arr, ARR_SIZE);
  insertion_sort(arr, ARR_SIZE);
  fprintf(stdout, "after bubble sort...\n");
  ARR_PRINT(arr, ARR_SIZE);

  return 0;
}
