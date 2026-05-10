#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Max_Size 10
#define ElemType int

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void BubbleSort_Min(ElemType arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    bool swapped = false;
    for (j = n - 1; j > i; j--) {
      if (arr[j - 1] > arr[j]) {
        swap(&arr[j - 1], &arr[j]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}

void BubbleSort(ElemType arr[], int n) {
  int i, j;

  for (i = 0; i < n - 1; i++) {
    bool swapped = false;

    for (j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        swapped = true;
      }
    }

    if (swapped == false) {
      break;
    }
  }
}

void init_arr(int *arr, int n) {
  int i;

  for (i = 0; i < n; i++) {
    arr[i] = rand() % 100 + 1;
  }
}

void print_arr(int *arr, int n) {
  int i;

  for (i = 0; i < n; i++) {
    fprintf(stdout, "%d", arr[i]);

    if (i != n - 1) {
      fprintf(stdout, " ");
    }
  }

  fprintf(stdout, "\n");
}

int main(void) {
  int *arr = (int *)malloc(sizeof(int) * Max_Size);

  if (arr == NULL) {
    perror("failed to initialize this arr");
    return EXIT_FAILURE;
  }

  memset(arr, 0, sizeof(int) * Max_Size);

  srand((unsigned)time(NULL));

  init_arr(arr, Max_Size);

  fputs("before BubbleSort: \n", stdout);
  print_arr(arr, Max_Size);

  // BubbleSort(arr, Max_Size);
  BubbleSort_Min(arr, Max_Size);

  fputs("after BubbleSort: \n", stdout);
  print_arr(arr, Max_Size);

  free(arr);

  return EXIT_SUCCESS;
}
