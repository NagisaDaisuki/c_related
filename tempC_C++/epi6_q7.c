#include <stdio.h>
#include <stdlib.h>

int find_max(int array[10]) {
  int i;
  int max = array[0];

  for (i = 1; i < 10; i += 1)
    if (array[i] > max)
      max = array[i];
  return max;
}

int main(void) {
  int array[10] = {10, 3, 5, 6, 7, 8, 9, 1, 2, 9};
  int max_num = find_max(array);
  char max_num_str = max_num + '0'; // 只对个位数生效
  // 可以使用sprintf 和 snprintf 实现数字转字符串
  char str[20]; // 足够大的缓冲区
  // snprintf函数原型 int snprintf(char *str, size_t size, const char *format,
  // ...)
  snprintf(str, sizeof(str), "%d", max_num);
  putchar(max_num_str);
  return EXIT_SUCCESS;
}
