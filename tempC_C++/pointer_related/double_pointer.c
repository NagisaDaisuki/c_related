#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int i;
  int *pi;
  int **ppi;

  printf("%d\n", ppi);
  printf("%d\n", &ppi);
  *pi = 5;

  ppi = &pi;
  *ppi = &i;

  return 0;
}
