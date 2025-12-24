#include <setjmp.h>
#include <signal.h>
#include <stdio.h>

// 全局跳转缓冲区
jmp_buf g_fpe_recover;

void fpe_handler(int sig);

int main(void) {

  // 注册信号处理函数
  signal(SIGFPE, fpe_handler);
  if (setjmp(g_fpe_recover) != 0) { // longjmp 跳转回来
    printf("恢复成功！将跳过本次错误计算，喵。\n");
    // 恢复后可以继续 main 循环
    goto next_calculation;
  }

  // 正常的、可能出错的计算
  int x = 10;
  int y = 0;
  fputs("尝试执行 10 / 0 的危险计算...\n", stdout);
  int result =
      x / y; // 这里会触发 SIGFPE, 程序会跳转到 setjmp(g_fpe_recover)的位置
  printf("计算结果：%d\n", result); // 这行代码不会被执行

next_calculation:
  printf("程序继续正常运行，喵。\n");
  return 0;
}

void fpe_handler(int sig) {
  // 在同步信号中安全地使用longjmp跳出，甚至使用printf
  printf("\n喵呜! 发生算术异常 (SIGFPE) 了，正在恢复...\n");

  longjmp(g_fpe_recover, 1);
}
