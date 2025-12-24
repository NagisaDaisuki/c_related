#include <math.h>
#include <stdio.h>
double score_sum(int a, int b, int c);

int main(void) {
  unsigned int a, b, c;
  a = b = c = 0;
  if (scanf("%d %d %d", &a, &b, &c) != 3)
    return -1;

  printf("%.0lf\n", floor(score_sum(a, b, c)));
  return 0;
}

double score_sum(int a, int b, int c) { return a * 0.2 + b * 0.3 + c * 0.5; }
