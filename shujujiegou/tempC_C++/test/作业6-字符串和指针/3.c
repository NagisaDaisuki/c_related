#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 80

int my_strncmp(const char *s1, const char *s2, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (*s1 != *s2) {
      return (int)*s1 - (int)*s2;
    }

    if (*s1 == '\0')
      break;

    s1++;
    s2++;
  }
  return 0;
}

int main(void) {
  int row = 0;
  int i;
  if (scanf("%d", &row) != 1 && row <= 0) {
    perror("Failed to receive row.");
    return EXIT_FAILURE;
  }

  // 清空缓冲区 换行符 \n
  while (getchar() != '\n' && !feof(stdin) && !ferror(stdin))
    ;

  char array[row][80];
  memset(array, 0, sizeof(array));

  for (i = 0; i < row; i++) {
    if (fgets(array[i], LENGTH, stdin) == NULL) {
      perror("Error string input.");
      return EXIT_FAILURE;
    }
  }
  int mark = 0;
  for (i = 1; i < row; i++) {
    if (my_strncmp(array[i], array[mark], LENGTH) < 0) {
      mark = i;
    }
  }
  fputs(array[mark], stdout);
  return EXIT_SUCCESS;
}
