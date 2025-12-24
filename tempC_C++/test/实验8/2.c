#include <stdio.h>
struct abc {
  char c;
  float v;
};

void fun1(struct abc b) {
  b.c = 'A';
  b.v = 80.7;
}

void fun2(struct abc *b) {
  (*b).c = 'C';
  (*b).v = 92.5;
}

int main(void) {
  struct abc a = {'B', 98.5};
  fun1(a);
  printf("%c,%.1f\n", a.c, a.v);
  fun2(&a);
  printf("%c,%.1f\n", a.c, a.v);
  return 0;
}
