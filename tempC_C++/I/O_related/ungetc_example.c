#include <ctype.h> // isdigit()
#include <stdio.h>

// 函数：从标准输入读取一个整数
int read_integer(FILE *stream);

int main(void) {
  int num1 /*,num2*/;
  // 第一次调用：读取123
  printf("请输入数据(例如：123ABC456)\n");

  num1 = read_integer(stdin);
  printf("读到的第一个整数：%d\n", num1);
  // 此时字符'A'被 read_integer 读走后又放回了stdin

  // 第二次调用：读取'A'
  printf("下一个字符是：%c\n", fgetc(stdin));

  // 第三次调用: 打印流中剩余部分
  int ch;
  while ((ch = getchar()) != EOF) {
    putchar(ch);
  }

  return 0;
}

int read_integer(FILE *stream) {
  int ch;
  int value = 0;

  // 1. 跳过开始的空白字符
  do {
    ch = fgetc(stream);
  } while (isspace(ch));

  // 2. 检查第一个非空白字符是否是数字
  if (!isdigit(ch)) {
    // 如果第一个字符不是数字，就把它放回流中。
    if (ch != EOF)
      ungetc(ch, stream);
    return 0; // EOF  返回一个错误代码
  }

  // 3. 读取数字部分
  while (isdigit(ch)) {
    value = value * 10 + (ch - '0');
    ch = fgetc(stream);
  }

  // 4. 核心步骤
  // 循环停止是因为 ch 遇到了第一个非数字字符或EOF
  // 这个非数字字符不属于当前的整数，它属于流的下一个部分。
  if (ch != EOF) {
    ungetc(ch, stream);
  }

  return value;
}
