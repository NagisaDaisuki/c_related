/* ---------------          莱布尼茨公式             ----------------------*/
// PI / 4 = 1 - 1 / 3 + 1 / 5 - 1 / 7 + ....

#include <math.h>
#include <stdio.h>

#define TARGET_PRECISION 1e-4

void compute_pi_approx() {
  double pi_over_4 = 0.0;   // 累加和，既 pi/4 的近似值
  double denominator = 1.0; // 分母，初始为 1
  double term;              // 当前项目的值
  int sign = 1;             // 符号，初始为 +1
  int count = 0;            // 计数器，初始为 0

  // 循环条件：在循环体内判断当前项是否达到停止条件
  do {
    // 1. 计算当前项的值: (+-) 1 / denominator;
    term = sign * (1.0 / denominator);

    // 2. 检查停止条件：如果当前项的绝对值小于目标精度，则跳出循环
    if (fabs(term) < TARGET_PRECISION)
      break;

    // 3. 累加到 pi / 4
    pi_over_4 += term;

    // 4. 更新下一轮的参数：
    sign *= -1;         // 符号取反
    denominator += 2.0; // 分母递增
    count++;            // 计数器累加

  } while (1); // 在内部使用break控制退出

  // 5. 计算 pi 值
  double pi = pi_over_4 * 4.0;

  // 精度为保留6位小数
  printf("pi=%.6f\n", pi);
  printf("count=%d\n", count);
}

int main(void) {
  compute_pi_approx();
  return 0;
}
