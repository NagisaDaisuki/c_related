#include <stdio.h>

int main(void) {
  union example {
    struct {
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

  printf("%d,%d\n", e.in.x, e.in.y);
}
