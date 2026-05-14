#include <stdio.h>

// 1. 统一函数签名
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div(int a, int b) { return (b != 0) ? a / b : 0; }

// 2. 使用 typedef 声明函数指针类型(推荐)
// 为了让函数指针可以存入同一个数组，它们必须具有相同的签名（参数类型和返回类型）
typedef int (*Operation)(int, int);

int main(void) {
  // 3. 定义和初始化函数指针数组
  Operation ops[4] = {
      add,
      sub,
      mul,
      div,
  };

  int result;
  int x = 20;
  int y = 5;

  printf("--- 函数指针数组应用：简易计算器： ---\n");

  // 4. 使用数组索引调用函数

  result = ops[0](x, y);
  printf("%d + %d = %d\n", x, y, result);

  result = ops[1](x, y);
  printf("%d - %d = %d\n", x, y, result);

  result = ops[2](x, y);
  printf("%d * %d = %d\n", x, y, result);

  // 使用间接调用方式
  result = (*ops[3])(x, y);
  printf("%d / %d = %d\n", x, y, result);

  return 0;
}
