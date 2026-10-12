#include <stdio.h>
#include <stdlib.h>

int main() {
  // 1. 初始状态: printf()输出到终端
  printf("-------- 程序开始 ----------\n");
  printf("这条信息应该显示在终端上。\n");

  // 2. 使用 freopen重定向 标准输出(stdout)
  // log.txt 新重定向的文件名
  // "w" 写入模式
  // stdout 要重定向的目标流
  FILE *original_stdout = freopen("./log.txt", "w", stdout);

  // 检查重定向是否成功
  if (original_stdout == NULL) {
    // 如果重定向失败，通常是文件路径问题
    perror("freopen failed.\n");
    exit(EXIT_FAILURE);
  }

  // 3. 重定向后的状态：printf 输出到 log.txt 文件
  printf("This information will showcase in log.txt instead of current "
         "terminal\n");
  fprintf(stdout,
          "freopen successfully change the direction of standard output.\n");
  fputs("-- 程序结束 --", stdout);

  // 4. 关闭文件流并返回
  // freopen 已经关闭了旧的 stdout(终端)， 并打开了新的文件

  return 0;
}
