#include <stdio.h>

void calculate_positive_sum() {
  int input_num; // 用户输入数
  int sum = 0;
  int count = 0;

  do {
    // 提示输入
    printf("Input a number:");

    // 检查 scanf 是否成功读取整数
    if (scanf("%d", &input_num) != 1) {
      // printf("error Input!");
      // 清理缓冲区并退出，避免无限循环
      while (getchar() != '\n' && getchar() != EOF)
        ;
      return;
    }

    // 判断输入是否为 0
    if (input_num == 0)
      break;

    // 判断是否为正数
    if (input_num > 0) {
      sum += input_num;
      count++;
    }
    // 负数不累加并进入下一次循环
  } while (1);

  // 输出结果
  printf("sum=%d, count=%d", sum, count);
}

int main(void) {
  calculate_positive_sum();
  return 0;
}
