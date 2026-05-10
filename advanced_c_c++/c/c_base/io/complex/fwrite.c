#include "player.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Player p1 = {101, 50, 99.5};
  FILE *file = fopen("save_data.bin", "wb");
  if (!file)
    return 1;

  fwrite(&p1, sizeof(Player), 1, file);
  printf("存档成功！\n");

  fclose(file);
  return 0;
}
