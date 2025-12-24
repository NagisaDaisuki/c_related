#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <errno.h>

double add(double a, double b) {
  if ((b > 0 && a > DBL_MAX - b) || (b < 0 && a < -DBL_MAX - b)) {
    fprintf(stderr, "Error: Addition overflow/underflow.\n");
    errno = ERANGE;
    return 0.0;
  }
  return a + b;
}

double sub(double a, double b) {
  if ((b < 0 && a > DBL_MAX + b) || (b > 0 && a < -DBL_MAX + b)) {
    fprintf(stderr, "Error: Subtraction overflow/underflow.\n");
    errno = ERANGE;
    return 0.0;
  }
  return a - b;
}

double mul(double a, double b) {
  if (a != 0 && b != 0 && fabs(a) > DBL_MAX / fabs(b)) {
    fprintf(stderr, "Error: Multiplication overflow.\n");
    errno = ERANGE;
    return 0.0;
  }
  return a * b;
}

double div_op(double a, double b) {
  if (0 == b) {
    fprintf(stderr, "Error: Division by zero is not allowed.\n");
    errno = EDOM;
    return 0.0;
  }
  if (fabs(b) < 1.0 && fabs(a) > DBL_MAX * fabs(b)) {
    fprintf(stderr, "Error: Division overflow.\n");
    errno = ERANGE;
    return 0.0;
  }
  return a / b;
}

