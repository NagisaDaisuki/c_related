#include <stdio.h>
#include <stdlib.h>
void luanshengsushu(int n);
int issushu(int n);

int main(void) {
  unsigned short int n = 0;
  if (scanf("%hu", &n) != 1)
    return -1;
  luanshengsushu(n);
  return EXIT_SUCCESS;
}

void luanshengsushu(int n) {
  int i;
  int arr[2];
  if (n < 5)
    printf("Empty\n");
  for (i = 3; i <= n; i++) {
    if (issushu(i)) {
      if (arr[0] == 0) {
        arr[0] = i;
      } else {
        arr[1] = i;
        if (arr[1] - arr[0] == 2) {
          printf("%d %d\n", arr[0], arr[1]);
        }
        arr[0] = arr[1];
        arr[1] = 0;
      }
    }
  }
}

int issushu(int n) {
  for (int i = 2; i < n; i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}
