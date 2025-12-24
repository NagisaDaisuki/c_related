#include "add.h"
#include "sub.h"
#include <stdio.h>

int main(void) {
  int a = 10, b = 5;
  printf("Result of addition: %d\n", add(a, b));
  printf("Result of subtraction: %d\n", sub(a, b));
  return 0;
}
