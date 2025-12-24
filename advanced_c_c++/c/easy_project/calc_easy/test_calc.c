#include "calc.h"
#include <errno.h>
#include <float.h>
#include <stdio.h>
#include <string.h>

void check_error(const char *op_name);

int main(void) {

  printf("Testing Addition Overflow:\n");
  errno = 0;
  add(DBL_MAX, DBL_MAX);
  check_error("Addition");

  printf("\nTesting Subtraction Overflow:\n");
  errno = 0;
  sub(-DBL_MAX, DBL_MAX);
  check_error("Subtraction");

  printf("\nTesting Multiplcation Overflow:\n");
  errno = 0;
  mul(DBL_MAX, 2.0);
  check_error("Multiplcation");

  printf("\nTesting Division Overflow:\n");
  errno = 0;
  div_op(DBL_MAX, 0.5);
  check_error("Division");

  printf("\nTesting Division by Zero:\n");
  errno = 0;
  div_op(10.0, 0.0);
  check_error("Division by zero");

  printf("\nTesting Normal Operations:\n");
  errno = 0;
  printf("1 + 1 = %f\n", add(1.0, 1.0));
  check_error("Normal Addition");
}

void check_error(const char *op_name) {
  if (errno != 0) {
    printf("%s failed with error: %s (errno: %d)\n", op_name, strerror(errno),
           errno);
    errno = 0; // Reset errno
  } else {
    printf("%s executed successfully.\n", op_name);
  }
}
