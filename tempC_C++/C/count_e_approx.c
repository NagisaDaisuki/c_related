#include <math.h>
#include <stdio.h>

// 目标精度：10的-5次方
#define TARGET_PRECISION 1e-6

void compute_e_approx();

int main(void) {
  compute_e_approx();
  return 0;
}
void compute_e_approx() {
  double e = 1.0;         // e 的初始值是公式的第一项：1
  double factorial = 1.0; // 阶乘的初始值：1! = 1 (用于第二项)
  double term = 1.0;      // 当前项的值，初始为 1/0! （虽然公式从 1/1!
                          // 开始，但是为了逻辑统一把 e=1.0 拆分到循环外）
  int count = 1;          // 计数器，初始值为 1 （对应 e = 1/0!）
  int n = 1;              // 循环递增的 n （代表 n!）

  // 循环条件：当前项的绝对值大于等于目标精度时继续
  // 注意：公式中 e 的初始值已经包含了 1.0，所以我们从 1/1! 开始累加。
  // 为了让循环体更简洁，我们让循环从 n = 1开始，term = 1.0 包含在 e 的初始值中
  // e 的初始值是 1 (1 / 0!)

  // 正式从 1/1! 开始累加
  while (fabs(term) >= TARGET_PRECISION) {
    // 1. 递推计算 n!: 新的 n! = (n - 1)! * n
    factorial *= n;
    // 2. 计算当前项的值：term = 1 / n!
    term = 1.0 / factorial;
    // 3. 判断是否达到停止条件
    if (fabs(term) < TARGET_PRECISION)
      break;
    // 4. 累加到e
    e += term;
    // 5. 累加项数和n
    count++;
    n++;
  }
  // 题目要求输出 e 的值和统计的项数
  // 注意：输出 count = 10 意味着公式中累加了 1/1! 到 1/9! 这 9 项，加上最开始的
  // 1，总共 10 项。 我们的 count = 1 是 base term (1/0!)，所以最终结果需要 +1

  printf("e = %.6f, count = %d\n", e, count);
}
