#include "add.h"
#include "mul.h"
#include "sub.h"
#include "sum.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  printf("use add func exec 1 + 2: \n");
  uint32_t end = addFunc(1, 2);
  printf("the ends of 1 + 2 = %d \n", end);

  printf("use sum func exec 1 - 2: \n");
  end = subFunc(1, 2);
  printf("the ends of 1 - 2 = %d \n", end);

  printf("use mul func exec 1 * 2: \n");
  end = mulFunc(1, 2);
  printf("the ends of 1 * 2 = %d \n", end);

  printf("use sum func exec 1 + 2: \n");
  end = sumFunc(1, 2);
  printf("the ends of 1 + 2 = %d \n", end);

  printf("hello world!\n");
  exit(0);
}
