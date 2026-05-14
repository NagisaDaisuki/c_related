#include <stdio.h>
#undef EOF
#define EOF -1

void mystery(int n) {
  n += 5;
  n /= 10;
  printf("%s\n", "**********" + 10 - n);
}

int main(void) {
  int n = 0;

  while (scanf("%d", &n) == 1 && n != EOF) {
    mystery(n);
  }

  return 0;
}
