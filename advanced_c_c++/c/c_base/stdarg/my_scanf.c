#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
// 使用 extern 声明 my_printf 函数
// extern 告诉编译器 函数的定义在其他编译单元中
extern void my_printf(const char *format, ...);

/*
 *  @brief me do scanf
 *  @param format is a string with it's placeholder
 *  @param ... variable argument list
 *  @return the num of integer va list contains
 * */
int my_scanf(const char *format, ...);

int main(void) {
  int a, b;
  a = b = 0;
  my_printf("请输入两个整数（例如：10 20）:\n");
  my_scanf("%d %d", &a, &b);
  my_printf("您输入了：%d 和 %d", a, b);
  return 0;
}

int my_scanf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  const char *p = format;
  int items_read = 0;

  // 假设输入流已经准备好,并且我们能逐个字符读取
  while (*p != '\0') {
    // 1. 跳过格式化字符串中的空格
    if (isspace((unsigned char)*p)) {
      // 在输入中跳过任意多的空白符
      int c;
      while ((c = getchar()) != EOF && isspace((unsigned char)c))
        ;
      if (c != EOF)
        ungetc(c, stdin); // 把非空白符放回
      p++;
      continue;
    }

    if (*p == '%') {
      p++; // 跳过 '%'

      // 吾辈这里只实现最简单的 %d
      if (*p == 'd') {
        // 关键点：va_arg 必须获取一个指针类型！
        int *target = va_arg(args, int *);

        int num = 0;
        int sign = 1;
        int c = getchar();

        // 跳过输入中的空白符（再次检查）
        while (isspace((unsigned char)c))
          c = getchar();

        // 检查负号
        if (c == '-') {
          sign = -1;
          c = getchar();
        } else if (c == '+') {
          c = getchar();
        }

        // 转换数字
        if (isdigit((unsigned char)c)) {
          do {
            num = num * 10 + (c - '0');
            c = getchar();
          } while (isdigit((unsigned char)c));

          // 将转换后的值存入可变参数提供的地址中
          *target = num * sign;
          items_read++;

          // 将最后一个非数字字符放回输入流
          if (c != EOF)
            ungetc(c, stdin);
        } else {
          // 如果不是数字开头，读取失败，应该返回
          if (c != EOF)
            ungetc(c, stdin);
          break;
        }
      }
      // TODO: 实现 %s, %c, %f 等...
    }
    p++;
  }

  va_end(args);
  return items_read;
}
