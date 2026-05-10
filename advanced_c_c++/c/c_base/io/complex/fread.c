#include "player.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Player p1;

  FILE *file = fopen("save_data.bin", "rb");
  if (!file) {
    printf("没有找到存档");
    return 1;
  }

  size_t ret = fread(&p1, sizeof(Player), 1, file);
  if (ret == 1) {
    printf("读档成功！ID: %d, Level: %d, HP: %.1f\n", p1.id, p1.level, p1.hp);
  } else {
    printf("读档失败，文件损坏！\n");
  }

  fclose(file);
  return EXIT_SUCCESS;
}
