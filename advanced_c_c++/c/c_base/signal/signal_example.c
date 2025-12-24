#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 信号处理函数
void handle_signal(int signum) {
  switch (signum) {
  case SIGINT:
    printf("\n捕获到 SIGINT 信号 (%d)！通常由 Ctrl+C 触发。\n", signum);
    break;
  case SIGTERM:
    printf("捕获到 SIGTERM 信号 (%d)！通常由 kill 命令触发。\n", signum);
    break;
  case SIGSEGV:
    printf("\n捕获到 SIGSEGV 信号 (%d)！程序发生了段错误。\n", signum);
    // 处理完同步信号后，通常无法安全地返回并继续执行，
    // 因为程序状态已损坏，最好的做法是清理资源并退出。
    exit(EXIT_FAILURE);
    break;
  default:
    printf("捕获到未知信号：%d\n", signum);
    break;
  }
}

int main(void) {
  // 1. 注册信号处理函数
  // signal() 函数返回的是旧的信号处理函数指针，这里我们忽略它。
  signal(SIGINT, handle_signal);
  signal(SIGTERM, handle_signal);
  signal(SIGSEGV, handle_signal);

  printf("程序已启动，PID：%d\n", getpid());
  printf("你可以新开一个终端，使用 'kill -TERM %d' 来发送 SIGTERM 信号。\n",
         getpid());
  printf("或者按下 Ctrl+C 来发送 SIGINT 信号。\n\n");

  sleep(2);

  // 2. 使用 raise() 触发一个异步信号 (SIGINT)
  printf("将在两秒后使用 raise(SIGINT) 触发 SIGINT 信号...\n");
  sleep(2);
  raise(SIGINT);

  // 3. 使用 raise() 触发另一个异步信号 (SIGTERM)
  printf("\n将在两秒后使用 raise(SIGTERM) 触发 SIGTERM 信号...\n");
  sleep(2);
  raise(SIGTERM);

  // 4. 故意触发一个同步信号 (SIGSEGV)
  printf("\n将在两秒后通过访问 NULL 指针来 触发 SIGSEGV 信号...\n");
  sleep(2);
  int *p = NULL;
  *p = 42; // 这将导致段错误，触发 SIGSEGV

  // 下面的代码将不会被执行，因为 SIGSEGV 处理函数会终止程序。
  // fprintf(stdout, "这行代码将不会被打印。\n");
  fputs("这行代码将不会被打印。", stdout);

  return 0;
}
