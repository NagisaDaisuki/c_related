#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // 用于 labs()

// 函数：不使用数学库判断一个数是否为完全立方数
bool is_perfect_cube_no_math(long n) {
  if (n == 0) {
    return true;
  }

  // 对绝对值进行二分查找
  long target = labs(n);
  long low = 1;
  long high = target;

  while (low <= high) {
    // 使用这种方式计算中间值，可以防止 low + high 可能的溢出
    long mid = low + (high - low) / 2;

    // mid 为0的情况在我们的逻辑中不会发生，因为 low 从1开始
    // 但作为一个健壮性检查，如果 mid 为0，则跳过
    if (mid == 0) {
      break;
    }

    // 将 mid 转换为 long long 以进行安全的立方计算
    long long mid_ll = mid;
    long long cube = mid_ll * mid_ll * mid_ll;

    // 检查立方计算是否溢出或大于目标
    // 如果 cube 变为负数，说明正数的计算发生了溢出
    if (cube < 0 || cube > target) {
      high = mid - 1;
    } else if (cube < target) {
      low = mid + 1;
    } else { // cube == target
      return true;
    }
  }

  return false;
}

int main() {
  long number;

  printf("请输入一个整数: ");
  if (scanf("%ld", &number) == 1) {
    if (is_perfect_cube_no_math(number)) {
      printf("%ld 是一个完全立方数。 \
",
             number);
    } else {
      printf("%ld 不是一个完全立方数。 \
",
             number);
    }
  } else {
    printf("无效的输入。\
");
  }

  return 0;
}
