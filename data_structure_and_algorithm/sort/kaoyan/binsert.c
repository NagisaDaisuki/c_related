#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Max_Size 11

void init_arr(int *arr, int n) {
  int i;
  for (i = 1; i < n; i++) {
    arr[i] = rand() % 50 + 1;
  }
}

void print_arr(int *arr, int n) {
  int i;
  for (i = 1; i < n; i++) {
    fprintf(stdout, "%d", arr[i]);
    if (i != n - 1)
      fputs(" ", stdout);
  }
  fputs("\n", stdout);
}

// 二分查找插入排序
void b_insertion_sort(int *arr, int n) {
  int i, j, mid, low, high;
  for (i = 2; i < n; i++) {
    arr[0] = arr[i];
    low = 1;      // 有序列表开头
    high = i - 1; // 有序列表的结尾，开始循环也就是arr[1]单个元素作为有序序列，
                  // 之后每次循环这个有序序列都会变大直到结束循环
    while (low <= high) {
      mid = (low + high) / 2; // 这里不需要用
      if (arr[mid] > arr[0]) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    } // 循环完后 low 就是我们要插入的位置

    // 如果 arr[0] 比有序区所有元素都大，二分结束后 low == i，
    // 此时 j = i - 1，j >= low 不成立，因此不会移动元素
    for (j = i - 1; j >= low; j--) {
      arr[j + 1] = arr[j];
    }
    arr[low] = arr[0];
  }
}

int main(void) {

  int *arr = (int *)malloc(sizeof(int) * Max_Size);
  if (arr == NULL) {
    perror("failed to init arr");
    return EXIT_FAILURE;
  }
  time_t t;
  srand((unsigned)time(&t));
  init_arr(arr, Max_Size);

  fputs("before sort: \n", stdout);
  print_arr(arr, Max_Size);
  b_insertion_sort(arr, Max_Size);
  fputs("after sort: \n", stdout);
  print_arr(arr, Max_Size);

  free(arr);
  return EXIT_SUCCESS;
}
