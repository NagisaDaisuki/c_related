/*
 *  鸡兔同笼
 *  98个头，386只脚
 *  鸡兔各有多少只？
 *
 *  鸡 x 兔 y
 *  头：x + y = 98
 *  脚：2x + 4y = 386
 *
 *  穷举法
    我们不需要解方程组，而是利用穷举法：

    假设鸡的数量 x 从 0 遍历到 98。

    根据头数方程，计算兔子的数量 y=98−x。

    检查当前的 (x,y) 组合是否满足脚数方程 2x+4y=386。
 * */
#include <stdio.h>

void solve_chicken_rabbit() {
  int total_heads = 98;
  int total_feat = 386;
  int x;
  int y;

  // 鸡的数量 x 取值范围为 0 到 98
  for (x = 0; x <= total_heads; x++) {
    // 1. 根据头数计算兔子数量y
    y = total_heads - x;

    // 2. 检查当前x 和 y 是否满足脚数条件
    if ((2 * x) + (4 * y) == total_feat) {
      printf("x=%d, y=%d\n", x, y);
      // 只有一个解
      return;
    }
  }
}

int main(void) {
  solve_chicken_rabbit();
  return 0;
}
