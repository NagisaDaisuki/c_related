#include <stdio.h>
#include <stdlib.h>

#define PUT_ARR_NUM(ARR, SIZE)                                                 \
  do {                                                                         \
    int __i, __j, count = 1;                                                   \
    for (__i = 0; __i < (SIZE); __i++)                                         \
      for (__j = 0; __j < (SIZE); __j++)                                       \
        (ARR)[__i][__j] = count++;                                             \
  } while (0)

#define ARR_PRINT(ARR, SIZE)                                                   \
  do {                                                                         \
    int __i, __j;                                                              \
    for (__i = 1; __i < (SIZE); __i++) {                                       \
      for (__j = 0; __j < __i; __j++) {                                        \
        printf("%4d", (ARR)[__i][__j]);                                        \
      }                                                                        \
      printf("\n");                                                            \
    }                                                                          \
  } while (0)

int main(void) {
  int n = 0;
  if (scanf("%d", &n) != 1 && n > 30) {
    perror("Failed to receive num.\n");
    return EXIT_FAILURE;
  }
#ifndef ARR_MAX
#define ARR_MAX n
#endif

  int arr[ARR_MAX][ARR_MAX];
  PUT_ARR_NUM(arr, n);
  ARR_PRINT(arr, n);

  return 0;
}
