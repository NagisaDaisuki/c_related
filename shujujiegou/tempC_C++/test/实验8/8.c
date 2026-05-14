#include <stdio.h>
int main(void) {
  struct example {
    union {
      int x;
      int y;
    } in;
    int a;
    int b;
  } e;
  e.a = 1;
  e.b = 2;
  e.in.x = e.a * e.b;
  e.in.y = e.a + e.b;
  printf("%d,%d", e.in.x, e.in.y);
  return 0;
}
