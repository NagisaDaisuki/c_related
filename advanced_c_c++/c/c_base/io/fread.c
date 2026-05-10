#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  int level;
  double hp;
} Player;

int main() {
  Player load_team[3]; // 准备一个空数组，用来接客

  // 1. 打开文件（rb = Read Binary，读二进制文件）
  FILE *file = fopen("save_data.bin", "rb");
  if (file == NULL) {
    perror("找不到存档文件");
    return 1;
  }

  // 2. 核心操作：把硬盘数据倒进内存！
  // 意思是：从 file 里每次读 sizeof(Player) 大小的数据，读 3 次，塞进 load_team
  // 中
  size_t read_count = fread(load_team, sizeof(Player), 3, file);

  // 3. 校验并打印
  printf("成功读取了 %zu 个玩家数据：\n", read_count);
  for (size_t i = 0; i < read_count; ++i) {
    printf("玩家[%d]: 等级=%d, 血量=%.1f\n", load_team[i].id,
           load_team[i].level, load_team[i].hp);
  }

  fclose(file);
  return 0;
}
