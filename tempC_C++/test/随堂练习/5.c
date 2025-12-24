#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSIGN_ARR(ARR, SIZE)                                                  \
  do {                                                                         \
    int __i;                                                                   \
    for (__i = 0; __i < (SIZE); __i++) {                                       \
      if (fscanf(stdin, "%d", &(ARR)[__i]) != 1) {                             \
        fprintf(stderr, "failed to receive arr elements.\n");                  \
        abort();                                                               \
      }                                                                        \
    }                                                                          \
  } while (0)

int main(void) {
  unsigned int t, n, m;
  t = n = m = 0;

  if (scanf("%u", &t) != 1)
    return -1;

  unsigned int c_1 = 1;
  while (c_1 <= t) {
    if (scanf("%u %u", &n, &m) != 2)
      return -1;
    int arr[n];
    memset(arr, 0, sizeof(arr));
    ASSIGN_ARR(arr, n);

    unsigned int c_2 = 1;
    while (c_2 <= m) {
      unsigned int op1, i_1, i_2, k;
      op1 = i_1 = i_2 = k = 0;
      int sum = 0;
      if (scanf("%u", &op1) != 1)
        return -1;

      switch (op1) {
      case 1:
        if (scanf("%u %u %u", &i_1, &i_2, &k) != 3)
          return -1;
        for (int i = i_1; i <= i_2; i++) {
          arr[i] += k;
        }
        break;
      case 2:
        if (scanf("%u %u", &i_1, &i_2) != 2)
          return -1;
        for (int i = i_1; i <= i_2; i++) {
          if (arr[i] % 2 == 0)
            sum += arr[i];
        }
        printf("%d\n", sum);
        break;
      default:
        fprintf(stdout, "wrong num\n");
        break;
      }
      c_2++;
    }
    c_1++;
  }
  return EXIT_SUCCESS;
}
