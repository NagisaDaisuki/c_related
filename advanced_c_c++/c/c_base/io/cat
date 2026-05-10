// 复印一个结构体数组
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  // 准备要在内存中写出的数据
  Player team[3] = {
      {101, 50, 99.5},
      {102, 30, 45.0},
      {103, 99, 150.0},
  };

  // 1. 打开文件 (wb = Write Binary 写 二进制 文件)
  FILE *file = fopen("sava_data.bin", "wb");
  if (file == NULL) {
    perror("文件打开失败");
    return 1;
  }

  // 2. 核心操作：一键复印内存!
  // 意思是：把 team 数组首地址开始，大小为 sizeof(Player)的数据，写 3 份到 file
  // 中
  size_t written_count = fwrite(team, sizeof(Player), 3, file);

  // 3. 检查有没有写够（及其良好的工程习惯）
  if (written_count != 3) {
    fprintf(stderr, "警告：只成功写入了 %zu 个 元素！\n", written_count);
  } else {
    printf("成功将 3 个玩家数据写入二进制文件！\n");
  }

  // 4. 关门
  fclose(file);

  return EXIT_SUCCESS;
}
