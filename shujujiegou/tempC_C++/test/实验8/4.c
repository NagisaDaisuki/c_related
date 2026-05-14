#include <stdio.h>
struct s {
  int a;
  float b;
  char *c;
};

int main(void) {
  static struct s x = {19, 83.5, "zhang"};
  struct s *px = &x;
  printf("%d %.1f %s\n", x.a, x.b, x.c);
  printf("%d %.1f %s\n", px->a, (*px).b, px->c);
  printf("%c %s\n", *px->c - 1, &px->c[1]);
  return 0;
}
