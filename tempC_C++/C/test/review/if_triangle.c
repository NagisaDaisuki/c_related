#include <stdio.h>
#include <stdlib.h>

void print_if_triangle();

int main(void) {
  print_if_triangle();
  return EXIT_SUCCESS;
}
void print_if_triangle() {
  float a, b, c;
  a = b = c = 0.0;
  while (scanf("%f %f %f", &a, &b, &c) != EOF) {
    if (a + b > c && a + c > b && b + c > a) {
      printf("Yes\n");
      continue;
    }
    printf("No\n");
  }
}
