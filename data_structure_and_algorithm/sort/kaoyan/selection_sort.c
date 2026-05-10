#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Elemtype int
#define Max_Size 10

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selectionSort(Elemtype arr[], int n) {
  int i, j, minIndex;

  for (i = 0; i < n - 1; i++) {
    minIndex = i;
    for (j = i + 1; j < n; j++) {
      if (arr[minIndex] > arr[j]) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      swap(&arr[i], &arr[minIndex]);
    }
  }
}

void init_arr(Elemtype arr[]) {
  int i;
  for (i = 0; i < Max_Size; i++) {
    arr[i] = rand() % 200 + 1;
  }
}

void print_arr(Elemtype arr[]) {
  int i;
  for (i = 0; i < Max_Size; i++) {
    fprintf(stdout, "%d", arr[i]);
    if (i != Max_Size - 1)
      fputs(" ", stdout);
  }
  fputs("\n", stdout);
}

int main(void) {
  int *arr = (int *)calloc(Max_Size, sizeof(int));
  time_t t;
  srand((unsigned)time(&t));
  if (arr == NULL) {
    perror("failed to init arr");
    return EXIT_FAILURE;
  }
  // memset(arr, 0, sizeof(int) * Max_Size); calloc会自动把空间初始为0

  init_arr(arr);
  print_arr(arr);
  fputs("\n", stdout);
  selectionSort(arr, Max_Size);
  print_arr(arr);
  return EXIT_SUCCESS;
}
