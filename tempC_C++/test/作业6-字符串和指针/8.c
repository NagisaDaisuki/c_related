#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 50

void rotate_n_char(char *s, int n);
void remove_newline(char *s);

int main(void) {
  char str[LENGTH];
  memset(str, 0, LENGTH);

  if (fgets(str, LENGTH, stdin) == NULL) {
    perror("Failed to input str.");
    return EXIT_FAILURE;
  }
  remove_newline(str);

  int n = 0;

  if (scanf("%d", &n) != 1) {
    fprintf(stderr, "wrong number input.\n");
  }
  rotate_n_char(str, n);

  printf("%s\n", str);
  return 0;
}

void rotate_n_char(char *s, int n) {
  if (n <= 0)
    return;

  char tmp[n];
  for (int i = 0; i < n; i++)
    tmp[i] = s[i];

  memmove(s, s + n, strlen(s) - n + 1); // 带上 \0
  strncat(s, tmp, n);
}

void remove_newline(char *s) {
  int n = strlen(s);
  if (n > 0 && s[n - 1] == '\n')
    s[n - 1] = '\0';
}
