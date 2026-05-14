#include <math.h>
#include <stdio.h>

double triangle_area(double a, double b, double c) { return 0.5 * (a + b + c); }

int main(void) {
  double a, b, c;
  printf("Input a,b,c:");
  scanf("%lf ,%lf,%lf", &a, &b, &c);
  if ((a + b) > c && (a + c) > b && (b + c) > a) {
    printf("area=%lf", triangle_area(a, b, c));
  } else
    printf("It is not a triangle");

  return 0;
}
