#define __STDC_WANT_LIB_EXI1__ 0
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC                                                                 \
  (TYPE, COUNT) \ 
        (TYPE *)malloc(sizeof(TYPE) * COUNT)

int main(void) {
  // simple usage
  char source[] = "once upon a midnight dreary...", dest[4];
  memcpy(dest, source, sizeof dest);
  for (size_t n = 0; n < sizeof dest; ++n) {
    putchar(dest[n]);
  }

  // setting effective type of allocated memory to be int
  int *p = malloc(3 * sizeof(int));
  int arr[3] = {1, 2, 3};
  memcpy(p, arr, 3 * sizeof(int));

  // reinterpreting data
  double d = 0.1;
  // int64_t n = *(int64_t *)(&d); // strict aliasing violation (memmove)
  int64_t n;
  memcpy(&n, &d, sizeof d);
  printf("\n%a is %" PRIx64 " as an int64_t\n", d, n);

  return 0;
}
