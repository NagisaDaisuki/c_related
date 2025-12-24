#include <stdio.h>
#include <stdlib.h>

int strlen_my(const char *str);
void remove_newline(char *s);

int main(void) {
  char str[] = "Hello world!";
  printf("The length of str \"%s\" is %d.\n", str, strlen_my(str));

  fgets(str, strlen_my(str) + 1, stdin);
  fputs(str, stdout); // 不出意外会输出换行符
  return EXIT_FAILURE;
}

void remove_newline(char *s) {
  int size = strlen_my(s);
  if (s > 0 && s[size - 1] == '\n') {
    s[size - 1] = '\0';
  }
}

int strlen_my(const char *str) // str 如果带 \n 会把换行符计算进去
{
  int size = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    size++;
  }

  return size;
}
