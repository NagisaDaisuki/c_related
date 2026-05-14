#include <stdio.h>
#include <stdlib.h>

void compute_rabbit_pairs() {
  int N; // 输入的月份数

  // 输入形式：一个整数
  if (scanf("%d", &N) != 1)
    return;

  // 斐波那契数列需要存储两个前项，这里用三个变量来递推
  long long f_n_minus_2 = 1; // 对应 F(n - 2)
  long long f_n_minus_1 = 1; // 对应 F(n - 1)
  long long current_f;       // 对应 F(n)

  int i;

  // 1. 处理前两个月的基础情况
  if (N >= 1)
    printf("%d %lld\n", 1, f_n_minus_2);
  if (N >= 2)
    printf("%d %lld\n", 2, f_n_minus_1);

  // 2. 从第三个月开始使用递推公式 F(n) = F(n - 1) + F(n - 2)
  for (i = 3; i <= N; i++) {
    // 计算当前项 F(n)
    current_f = f_n_minus_1 + f_n_minus_2;

    // 按照输出格式要求输出：月数和兔子对数，空格分割
    printf("%d %lld\n", i, current_f);

    // 更新前两项，为下一次迭代做准备
    // F(n - 2) 变成 F(n - 1)
    f_n_minus_2 = f_n_minus_1;
    // F(n - 1) 变成 F(n)
    f_n_minus_1 = current_f;
  }
}

int main(void) {
  // 斐波那契数列增长很快，使用 long long 类型可以防止溢出
  // 即使 N = 12, F(12) = 233， 用int足够，但养成习惯用 long long 更安全。
  compute_rabbit_pairs();
  return 0;
}
