#include <stdio.h>

// 一个通用的宏定义循环数组
#define ARR_PRINT(ARR, SIZE)                                                   \
  do {                                                                         \
    int __i;                                                                   \
    for (__i = 0; __i < (SIZE); __i++)                                         \
      printf("%d:%d\n", __i, (ARR)[__i]);                                      \
  } while (0)

// 编译器尝试在调用点展开函数，消除函数调用开销
static inline void arr_print_func(int *arr, size_t size) {
  size_t i;
  for (i = 0; i < size; i++)
    printf("%zu:%d\n", i, arr[i]);
}

void print_count(int *arr, size_t size) {
  int n, count;
  n = count = 0;

  while (count <= 50) {

    if (scanf("%d", &n) == 1 && n >= 0 && n <= 4) {
      count++;
      switch (n) {
      case 0:
        arr[0] += 1;
        break;
      case 1:
        arr[1] += 1;
        break;
      case 2:
        arr[2] += 1;
        break;
      case 3:
        arr[3] += 1;
        break;
      case 4:
        arr[4] += 1;
        break;
      }
    }

    if (n == -1)
      break;
  }

  arr_print_func(arr, size);
}

int main(void) {
  int arr_count[5] = {0};
  int arr_size = sizeof(arr_count) / sizeof(arr_count[0]);
  print_count(arr_count, arr_size);
  return 0;
}
