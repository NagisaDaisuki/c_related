#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // 1. 初始状态：printf输出到终端
  printf("--- 程序开始 ---\n");
  printf("这条信息应该显示在终端上。\n");

  // =======================================================
  // 2. 使用 freopen 重定向标准输出 (stdout)
  //    参数:
  //      "log.txt": 新的文件名
  //      "w": 写入模式 (会覆盖文件原有内容)
  //      stdout: 要重定向的目标流
  // =======================================================
  FILE *original_stdout = freopen("./log.txt", "w", stdout);
  // 将 stdout流 重定向到 log.txt

  // 检查重定向是否成功
  if (original_stdout == NULL) {
    // 如果重定向失败，通常是文件路径的问题
    perror("failed to execute freopen.");
    exit(EXIT_FAILURE);
  }

  // 3. 重定向后的状态： printf 输出到 log.txt 文件
  printf("这条信息不会显示在终端，而是写入 log.txt。\n");
  printf("freopen 成功地将标准输出改变了方向。\n");
  printf("--- 程序结束 ---\n");

  // 4. 关闭文件流并返回
  // freopen 已经关闭了旧的 stdout（终端），并打开了新的文件。
  // 程序结束时会自动关闭 log.txt，但明确关闭是好习惯

  if (fclose(stdout) !=
      0) // 这里 关闭 (original_stdout)也是一样的，因为指向的是一个FILE*
  {
    perror("failed to close stdout!");
  }

  // 程序不会输出任何成功信息到终端，因为它被重定向了
  return 0;
}
