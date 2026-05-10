#include <memory.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Max_Size 10
#define ElemType int

// void swap(ElemType *a, ElemType *b) {
//   ElemType temp = *a;
//   *a = *b;
//   *b = temp;
// }

void BinaryInsertionSort(ElemType A[], int n) {
  int i, j, low, high, mid;

  for (i = 2; i <= n; i++) {
    A[0] = A[i]; // 主要作用就是暂存元素，和插排的功能不太一样，插排还有防溢出

    low = 1; // 折半查找的范围
    high = i - 1;
    while (low <= high) {
      mid = (low + high) / 2;

      if (A[mid] > A[0]) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }

    // 給 low 位置及其后面的元素 整体 右移一格，給A[i]腾位置
    // 如果 原本前驱序列就有序，那么 上面的 while 循环得出的 low = i
    // 那么 j = i - 1,j的值不会大于等于low 下面的for循环不会动
    // 哨兵 1 3 5 7 9 这个序列假如 i = 5也就是 A[5] 要插入到前面的序列
    // 哨兵 1 3 5 7, 但是前面是有序序列，while循环最终给出的 low = i
    // 也就是 直接不用动 下面的 for循环 直接 大于 low
    for (j = i - 1; j >= low; j--) {
      A[j + 1] = A[j];
    }
    A[low] = A[0];
  }
}

void init_arr(ElemType *arr) {
  int i;
  for (i = 0; i < Max_Size; i++) {
  }
}

void print_arr(ElemType *arr) {}

int main(void) {

  int *arr = (int *)malloc(Max_Size * sizeof(int));
  if (arr == NULL) {
    perror("failed to init arr");
    return EXIT_FAILURE;
  }

  memset(arr, 0, Max_Size * sizeof(int));

  time_t t;
  srand((unsigned)time(&t));

  return EXIT_SUCCESS;
}
