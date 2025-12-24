#include "calc.h"
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// errno是一个存储在线程局部存储区(TLS)的值，其实errno是一个宏这个宏是一个函数调用返回一个指向
// int 的指针然后解引用。
// #define errno (*__errno_location())
// 每个线程都有自己独立的一份errno。
// 在同一个线程内(main函数调用add函数)add函数修改了它，main函数就可以读取到。

// double add(double a, double b) { return a + b; }
double add(double a, double b) {
  if ((b > 0 && a > DBL_MAX - b) || (b < 0 && a < -DBL_MAX - b)) {
    fprintf(stderr, "Error: Addition overflow/underflow.\n");
    errno = ERANGE;
    return 0.0;
  }
  return a + b;
}

// double sub(double a, double b) { return a - b; }
double sub(double a, double b) {
  if ((b < 0 && a > DBL_MAX + b) || (b > 0 && a < -DBL_MAX + b)) {
    fprintf(stderr, "Error: Subtraction overflow/underflow.\n");
    errno = ERANGE;
    return 0.0;
  }
  return a - b;
}

// double mul(double a, double b) { return a * b; }
double mul(double a, double b) {
  if (a != 0 && b != 0 && fabs(a) > DBL_MAX / DBL_MAX / fabs(b)) {
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
