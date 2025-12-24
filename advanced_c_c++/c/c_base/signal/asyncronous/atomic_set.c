#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t g_signal_received = 0;

void safe_exit_handler(int sig) {
  // 黄金法则：只设置标志
  g_signal_received = sig;
  // 不调用 printf ！不调用 malloc ！不调用任何非异步安全的库函数
}

int main() {
  signal(SIGINT, safe_exit_handler);
  printf("程序运行中。按 Ctrl+C 退出。\n");

  while (g_signal_received == 0) {
    // 核心工作
    sleep(1);
  }

  // 主循环安全检测到标志被设置后，可以安全地执行复杂清理。
  printf("\n收到信号 %d，正在执行安全清理...\n", g_signal_received);
  // 此时可以安全调用 fclose() ，free(), printf()等标准库函数。
  exit(0);
}
