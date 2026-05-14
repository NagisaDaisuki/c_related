#include <stdio.h>

int main(void) {
  int num;
  printf("Input a integer number:");
  scanf("%d", &num);
  if (num % 2 == 0)
    printf("a is an even number");
  else
    printf("a is an odd number");

  return 0;
}
