#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Max_Size 10
#define ElemType int

void InsertionSort(ElemType A[], int n) {
  int i, j;
  for (i = 2; i <= n; i++) { // 依次将A[2]~A[n]插入前面已排列序列
    if (A[i] < A[i - 1]) {   // 若A[i]关键码小于A[i - 1]将其插入有序表
      A[0] = A[i];           // 复制为哨兵 A[0]不存储元素
      for (j = i - 1; A[0] < A[j]; j--) {
        A[j + 1] = A[j];
      }
      A[j + 1] = A[0];
    }
  }
}

void init_arr(int arr[]) {
  int i;

  for (i = 1; i <= Max_Size; i++) {
    arr[i] = rand() % 50 + 1;
  }
}

void print_arr(int arr[]) {
  int i;

  for (i = 1; i <= Max_Size; i++) {
    fprintf(stdout, "%d", arr[i]);
    if (i != Max_Size)
      fprintf(stdout, " ");
  }
  fprintf(stdout, "\n");
}

int main(void) {
  int arr[Max_Size + 1];
  memset(arr, 0, sizeof(arr));
  time_t t;
  srand((unsigned)time(&t));
  init_arr(arr);
  fprintf(stdout, "before InsertionSort: \n");
  print_arr(arr);
  InsertionSort(arr, Max_Size);
  fprintf(stdout, "after InsertionSort: \n");
  print_arr(arr);
}
