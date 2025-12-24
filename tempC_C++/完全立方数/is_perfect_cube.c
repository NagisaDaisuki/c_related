#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// 函数：判断一个长整型数 n 是否为完全立方数
bool is_perfect_cube(long n) {
  // 0 是 0 的立方，是一个完全立方数
  if (n == 0) {
    return true;
  }

  // 使用 long double 以获得更高精度
  // cbrtl 函数可以正确处理正数和负数
  long double root = cbrtl(n);

  // 将计算出的根四舍五入到最接近的整数
  long root_rounded = roundl(root);

  // 将四舍五入后的整数再进行立方运算
  // 使用 long long 来存储立方结果，以防止在计算过程中发生溢出
  long long check_cube = (long long)root_rounded * root_rounded * root_rounded;

  // 检查计算出的立方是否与原数相等
  return check_cube == n;
}

int main() {
  long number;

  printf("请输入一个整数: ");
  if (scanf("%ld", &number) == 1) {
    if (is_perfect_cube(number)) {
      printf("%ld 是一个完全立方数。 \
",
             number);
    } else {
      printf("%ld 不是一个完全立方数。 \
",
             number);
    }
  } else {
    printf("无效的输入。 \
");
  }

  return 0;
}
