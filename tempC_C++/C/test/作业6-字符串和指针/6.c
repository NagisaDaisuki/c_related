#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 80

int main(void) {
  char a[LENGTH];
  memset(a, 0, sizeof(a));

  if (fgets(a, LENGTH, stdin) == NULL) {
    perror("Failed to receive a.");
    return EXIT_FAILURE;
  }

  int mark = 0, i;
  for (i = 1; i < strlen(a); i++) {
    if (a[i] > a[mark])
      mark = i;
  }

  char *insert_pos = &a[mark + 1];
  size_t move_len = strlen(insert_pos) + 1; // 移动的长度(包括'\0')

  memmove(insert_pos + 2, insert_pos, move_len);

  a[mark + 1] = 'a';
  a[mark + 2] = 'b';

  printf("%s", a);
  return 0;
}
