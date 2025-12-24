#include <stdio.h>
#define N 5
#define LEN 20

int main() {
  char name[N][LEN];
  char *name2[N];
  char **p;
  int i;
  for (i = 0; i < 5; i++) {
    fgets(name[i], LEN, stdin);
    name2[i] = name[i];
  }

  for (i = 0; i < 5; i++) {
    p = name2 + i;
    printf("%s\n", *p);
    printf("%c\n", **p);
  }
  return 0;
}
