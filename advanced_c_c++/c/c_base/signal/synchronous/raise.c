#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void reset_handler(int sig) {
  fputs("收到内部重置信号（SIGUSR1），正在重载配置...\n", stdout);
  // 这里上下文是可控的，可以调用一些简单的库函数，例如日志记录
  // 但仍然要小心哪些依赖全局状态的复杂库函数！
  fputs("配置重载完成，喵。\n", stdout);
  // 这里有两个选项，将SIGUSR1信号的处理函数重新设置为reset_handler在下一次处理
  // SIGUSR1 信号时也调用 reset_handler, 还有一种选项是不设置，那下一次
  // SIGUSR1 信号发生的时候就是缺省处理SIG_DFL
  // signal(SIGUSR1, reset_handler);
}

int main(void) {
  //
  // 在现代POSIX兼容系统中推荐使用
  // sigaction()函数来设置信号处理器，因为它提供了更可靠，更细致的控制
  // sigaction函数默认不重置信号处理函数为SIG_DFL
  // 同时sigaction运行在信号处理函数执行期间自动阻塞同一信号（阻塞同类信号）
  // 从而安全地避免无限递归或竞态条件。
  // signal(SIGUSR1, reset_handler);

  // 1. 定义 sigaction 结构体
  struct sigaction sa;

  // 清空结构体
  memset(&sa, 0, sizeof(sa));

  // 2. 设置新的处理函数
  // sa_handler 字段接受我们定义的 reset_handler 函数指针
  sa.sa_handler = reset_handler;
  // 设置标志：sa_flags
  // 默认情况下，sa_flags = 0，这意味着：
  // a) 处理器执行时，SIGUSR1 会被阻塞（防止递归）。
  // b) 处理器执行后，不会自动恢复为 SIG_DFL。

  // 3. 调用 sigaction() 注册信号处理器
  // 参数1: 信号编号 (SIGUSR1)
  // 参数2: 新的处理方式 (&sa)
  // 参数3: 旧的处理方式 (NULL，表示我们不关心旧值)
  if (sigaction(SIGUSR1, &sa, NULL) == -1) {
    perror("喵呜！注册 SIGUSR1 失败了");
    return 1;
  }

  printf("程序启动，使用 sigaction "
         "注册信号处理器。按'R'然后回车来触发信号，喵。\n");
  while (1) {
    char input = getchar();
    if (input == 'R' || input == 'r') {
      // 主动触发信号给自身，这是同步信号的一种形式
      fprintf(stdout, "--- 触发内部 SIGUSR1 信号 ---\n");
      raise(SIGUSR1);
    } else if (input == 'Q' || input == 'q') {
      break;
    }
  }

  return 0;
}
