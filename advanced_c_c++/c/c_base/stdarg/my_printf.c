#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

// 辅助函数：将整数转换为字符串并打印
/*
 *  @brief switch integer to string and print
 *  @param n integer
 *  @return void
 * */
void put_int(int n);

/*
 *  @brief me define printf
 *  @param const char *format input string with placeholder
 *  @param ... variable argument lists
 *  @return void
 * */
void my_printf(const char *format, ...);

// int main(void) {
//   my_printf("喵呜~ 这是我自制的printf！\n");
//   my_printf("测试：整数 %d, 字符 %c, 字符串 %s, 负数 %d,百分号%%\n", 123,
//   'K',
//             "Hello C", -456, 1);
//   return 0;
// }

void put_int(int n) {
  char buffer[12];                         // 足够存储 32 位整数
  char *ptr = buffer + sizeof(buffer) - 1; // char *ptr = &buffer[11];
  *ptr = '\0';

  // 处理负数
  int is_negative = 0;
  if (n < 0) {
    is_negative = 1;
    n = -n;
  }

  // 至少打印一位数字(n = 0)
  do {
    *(--ptr) = (n % 10) + '0';
    n /= 10;
  } while (n > 0);

  if (is_negative) {
    *(--ptr) = '-';
  }

  write(STDOUT_FILENO, ptr, buffer + sizeof(buffer) - 1 - ptr);
}

void my_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  const char *p = format;

  while (*p != '\0') {
    if (*p == '%') {
      p++; // 跳过 ‘%’
      switch (*p) {
      case 'd': // 处理整数
      {
        int val = va_arg(args, int); // 获取 int 类型参数
        put_int(val);
      } break;
      case 'c': // 处理字符
      {
        int val = va_arg(args, int); // 字符被提升为 int
        write(STDOUT_FILENO, &val, 1);
      } break;
      case 'h': // 处理 短整型
      {
        int val = va_arg(args, int);
        write(STDOUT_FILENO, &val, 1);
      } break;
      case 's': // 处理字符串
      {
        char *s = va_arg(args, char *); // 获取 char *类型参数
        if (s == NULL)
          s = "(null)";
        // 简化 strlen和write
        while (*s != '\0') {
          write(STDOUT_FILENO, s++, 1);
        }
      } break;
      case '%': // 处理 %%
        write(STDOUT_FILENO, "%", 1);
        break;
      default:
        // 处理未识别的格式符，打印 % 和后面的字符
        write(STDOUT_FILENO, "%", 1);
        write(STDOUT_FILENO, p, 1);
        break;
      }
    } else {
      write(STDOUT_FILENO, p, 1);
    }
    p++;
  }

  va_end(args);
}
