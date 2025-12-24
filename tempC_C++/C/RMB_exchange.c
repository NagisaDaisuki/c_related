/*
 *
    用一张100元人民币兑换10元、5元和1元的纸币（每一种都要有）共50张，
    请用穷举法编程计算共有几种兑换方案，每种方案各兑换多少张各类纸币。
    x：兑换的 10 元纸币张数
    y：兑换的 5 元纸币张数
    z：兑换的 1 元纸币张数
 *
 *  10x + 5y + 1z = 100
 *  x + y + z = 50
 *  x >= 1 y >= 1 z >= 1
    我们选择 x 和 y 作为穷举变量，然后利用张数约束来计算 z，
     最后检查金额约束是否满足。
 * */

#include <stdio.h>

void exchange_rmb() {
  int x;
  int y;
  int z;
  int count = 0;

  for (x = 1; x <= 9; x++) {
    for (y = 1; y <= 50 - x - 1; y++) {
      z = 50 - x - y;
      if ((10 * x) + (5 * y) + z == 100) {
        count++;
        printf("x=%d, y=%d, z=%d\n", x, y, z);
      }
    }
  }
  printf("count=%d\n", count);
}

int main(void) {
  exchange_rmb();
  return 0;
}
