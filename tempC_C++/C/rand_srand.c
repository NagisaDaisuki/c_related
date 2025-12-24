#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int i, n;
  time_t t; // <time.h>

  n = 5;
  printf("Time: %ld\n", time(&t));
  // 初始化随机数发生器
  srand((unsigned)time(&t));

  // 输出 0 到 49 之间的 5 个随机数
  for (i = 0; i < n; i++) {
    printf("%d\n", rand() % 50);
  }

  // 输出 1 到 50 之间的 5 个随机数
  for (i = 0; i < n; i++) {
    printf("%d\n", rand() % 50 + 1);
  }

  return 0;
}
