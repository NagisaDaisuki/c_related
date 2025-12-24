#include <stdarg.h>
#include <stdio.h>

void my_log(const char *format, ...);

int main(void) {
  my_log("Everything I found great was sunfaded.");
  my_log("LoginName: %s", "Akeboshi Himari");
  my_log("LoginPassword: %s", "1145141919810");
  return 0;
}

void my_log(const char *format, ...) {
  va_list args;
  va_start(args, format);

  // 使用 vprintf 将格式化字符串和参数列表打印到标准输出
  printf("LOG: ");
  vprintf(format, args);
  printf("\n");

  va_end(args);
}
