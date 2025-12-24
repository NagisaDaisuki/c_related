#include <stdarg.h>
#include <stdio.h>

/*
 *  @brief 计算所有传入整数参数的和
 *  @param count 必须传入的固定参数，表示后面有多少个整数参数
 *  @param ... 剩下的可变参数
 *  @return 所有整数的和
 * */
int sum_all(int count, ...);
void binary_to_ascii(unsigned int n);

int main(void) {
  // 调用示例1：求 3 个数的和（10 + 20 + 30）
  int total1 = sum_all(3, 10, 20, 30);
  fputs("Sum of 3 numbers: \n", stdout);
  binary_to_ascii(total1);
  fputs("\n", stdout);
  // 调用示例2：求 5 个数的和 （1 + 2 + 3 + 4 + 5）
  int total2 = sum_all(5, 1, 2, 3, 4, 5);
  fputs("Sum of 5 numbers: \n", stdout);
  binary_to_ascii(total2);
  puts("");
  return 0;
}

int sum_all(int count, ...) {
  // 1. 定义 va_list 变量
  va_list args;
  int sum = 0;
  int i;

  // 2. 初始化 va_list 变量
  // args 现在指向 count 之后的第一个参数
  va_start(args, count);

  // 3. 循环获取参数
  for (i = 0; i < count; i++) {
    // 使用 va_arg 获取下一个参数，并指定其类型为 int
    // 每次调用都会自动将 args 推进到下一个参数
    int num = va_arg(args, int);
    sum += num;
  }

  // 4. 清理 va_list
  va_end(args);

  return sum;
}

void binary_to_ascii(unsigned int n) {
  unsigned int quotient = n / 10;

  if (quotient != 0)
    binary_to_ascii(quotient);
  putchar(n % 10 + '0');
}
