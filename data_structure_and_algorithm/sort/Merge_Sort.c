#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t t;

#define Max_Size 10

void MergeSortRange(int arr[], int temp[], int left, int mid, int right) {
  int i = left;    // 左分区当前元素
  int j = mid + 1; // 右分区当前元素
  int k = left;    // temp 数组当前元素

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }

  while (i <= mid)
    temp[k++] = arr[i++];
  while (j <= right)
    temp[k++] = arr[j++];

  for (int p = 0; p <= right; p++) {
    arr[p] = temp[p];
  }
}

void MergeSortImpl(int arr[], int temp[], int left, int right) {
  if (left >= right)
    return;

  int mid = left + (right - left) / 2;

  MergeSortImpl(arr, temp, left, mid);
  MergeSortImpl(arr, temp, mid + 1, right);

  MergeSortRange(arr, temp, left, mid, right);
}

void MergeSort(int arr[], int n) {
  if (n < 2)
    return;
  int *temp = (int *)malloc(sizeof(int) * n);
  MergeSortImpl(arr, temp, 0, n - 1);

  free(temp);
}

void init_arr_with_rand(int arr[], int n) {

  int i;
  for (i = 0; i < n; i++) {
    arr[i] = rand() % 100 + 1;
  }
}

void print_arr(int arr[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    fprintf(stdout, "%d ", arr[i]);
  }
  fputs("\n", stdout);
}

void print_arr_invert(int arr[], int n) {
  int i;
  for (i = n - 1; i >= 0; i--) {
    fprintf(stdout, "%d ", arr[i]);
  }
  fputs("\n", stdout);
}

int main() {
  int *arr = (int *)malloc(sizeof(int) * Max_Size);
  if (arr == NULL) {
    perror("failed to init arr!");
    return 1;
  }

  srand((unsigned)time(&t));
  init_arr_with_rand(arr, Max_Size);
  fprintf(stdout, "before MergeSort: \n");
  print_arr(arr, Max_Size);
  MergeSort(arr, Max_Size);
  fprintf(stdout, "after MergeSort: \n");
  print_arr_invert(arr, Max_Size);

  free(arr);
  return 0;
}
