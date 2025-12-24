#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

jmp_buf g_jmp_buffer;

void alarm_handler(int sig) {
  // 可以使用 longjmp 安全地跳回主程序，结束阻塞操作
  longjmp(g_jmp_buffer, 1);
}

void blocking_read_with_timeout() {
  // 1. 设置信号处理器
  signal(SIGALRM, alarm_handler);

  // 2. 设置跳回点
  if (setjmp(g_jmp_buffer) != 0) {
    printf("\n 读取操作超时啦！\n");
    return; // 从 longjmp跳回，执行超时逻辑
  }

  // 3. 启动定时器：10秒
  alarm(10);
  printf(
      "正在等待输入（10秒后超时）...\n"); // 这里如果不写\n将不会立即写入缓冲区

  // 4. 执行可能阻塞的 I/O 操作
  char buffer[100];
  read(STDIN_FILENO, buffer, 100);

  // 5. 成功读取后，取消定时器
  alarm(0);

  printf("读取成功！\n");
}

int main(void) {
  blocking_read_with_timeout();
  return 0;
}
