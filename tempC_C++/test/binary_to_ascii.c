#include <stdio.h>

void binary_to_ascii(unsigned int value) {
  unsigned int quotient;

  quotient = value / 10;

  if (quotient != 0)
    binary_to_ascii(quotient);
  putchar(value % 10 + '0');
}

int main(void) {

  int value = 1e5;
  binary_to_ascii(value);
  printf("\n");
  putchar("0123456789ABCDEF"[value % 16]);
  printf("\n");
  return 0;
}
