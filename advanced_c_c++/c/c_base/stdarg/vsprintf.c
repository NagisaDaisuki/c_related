#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 256

// 封装函数：将格式化输出写入到字符串
/*
 *  @brief package function and write down output format to string
 *  @param  buffer is the container of format string
 *  @param  format is the requirement value of vsprintf function
 *  @param  ... is variables argument list
 *  @return return actual format with va_list length
 * */
int format_message(char *buffer, const char *format, ...);

int main(void) {

  char output[MAX_BUFFER];
  memset(output, 0, sizeof(output));

  format_message(output, "%d is the real value of world!\n", 42);
  fprintf(stdout, "%s", output);
  return EXIT_SUCCESS;
}
int format_message(char *buffer, const char *format, ...) {
  va_list args;
  va_start(args, format);

  // 使用 vsnprintf 代替 vsprintf，因为它接受缓冲区大小参数，更安全
  // vsnprintf 是 vprintf 系列中用于写入字符串的最佳实践
  int result = vsnprintf(buffer, MAX_BUFFER, format, args);

  va_end(args);
  return result;
}
