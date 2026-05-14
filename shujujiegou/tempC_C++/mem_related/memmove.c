#define __STDC_WANT_LIB_EXT1__ 1
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char str[] = "1234567890";
  puts(str);
  memmove(str + 4, str + 3, 3);
  puts(str);

  int *p = malloc(3 * sizeof(int));
  int arr[3] = {1, 2, 3};
  memmove(p, arr, 3 * sizeof(int));

  double d = 0.1;
  int64_t n;
  memmove(&n, &d, sizeof d);
  printf("%a is %" PRIx64 " as an int64_t\n", d, n);

  return 0;
}
