#include <signal.h>
#include <stdio.h>
#include <stdlib.h> // _Exit()
#include <string.h>
#include <unistd.h> // _exit()

void debug_handler(int sig) {
  // 保证安全： 只使用异步安全的函数(write)
  const char *msg = "发生 SIGSEGV 致命错误！\n";

  // 向文件描述符 2 （标准错误 stderr）写入信息。
  write(STDERR_FILENO, msg, strlen(msg));

  // 立即安全退出
  _Exit(1);
}

// 在main函数中：
// signal(SIGSEGV, debug_handler)

int main(void) {
  signal(SIGSEGV, debug_handler);

  int *p = NULL;
  *p = 42;
  // 这里触发了SIGSEGV信号，检测到对内存的非法访问

  const char *msg = "Anyway, this comment will not show in termianl.";
  write(STDOUT_FILENO, msg, strlen(msg));

  return EXIT_SUCCESS;
}
