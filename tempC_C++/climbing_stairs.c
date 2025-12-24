/*
 *  动态规划(Dynamic Programming)问题，爬楼梯问题
 *  核心思想是通过递推关系来解决
 *  假设 F(n) 是爬到第n级台阶的不同方式总数。
 *  要爬到第n级台阶，只能通过以下两种方式到达。
 *
 *  从第 n−1 级台阶迈上 1 阶：到达第 n−1 级的方式有 F(n−1) 种。
    从第 n−2 级台阶迈上 2 阶：到达第 n−2 级的方式有 F(n−2) 种。

    由于这两种方式是互斥的，所以到达第 n 级台阶的总方式数就是这两种方式的总和：
 *  F(n) = F(n - 1) + F(n - 2)
 *
 *  初始条件（边界情况）
 *
 *  第一级台阶(n = 1)
 *  F(1) = 1 // 一种方式
 *  第二级台阶(n = 2)
 *  1. 走 1阶 + 1阶
 *  2. 走 2阶
 *  F(2) = 2 // 两种方式
 *
 * */
#include <stdio.h>

void climbing_stairs(int N);
int main(void) {
  int N;
  while (scanf("%d", &N) == 1)
    climbing_stairs(N);
  return 0;
}

void climbing_stairs(int N) {

  if (N < 1) {
    printf("0\n");
    return;
  }

  // 边界条件处理
  if (N == 1) {
    printf("1\n");
    return;
  }
  if (N == 2) {
    printf("2\n");
    return;
  }

  // 动态规划/递推变量
  // f_n_minus_2 对应 F(n - 2),初始值为 F(1)
  int f_n_minus_2 = 1;
  // f_n_minus_1 对应 F(n - 1),初始值为 F(2)
  int f_n_minus_1 = 2;
  int current_f = 0; // 对应 F(n)

  int i;

  // 从 n = 3 开始迭代计算
  for (i = 3; i <= N; i++) {
    // 递推公式：F(n) = F(n - 1) + F(n - 2);
    current_f = f_n_minus_1 + f_n_minus_2;

    // 更新前两项，为下一次迭代做准备
    f_n_minus_2 = f_n_minus_1;
    f_n_minus_1 = current_f;
  }

  // 最终结果是 F(N)
  printf("%d\n", current_f);
}
