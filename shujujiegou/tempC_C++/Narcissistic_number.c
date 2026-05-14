#include <stdio.h>

void find_narcissistic_numbers() {
  int n;
  int hundreds;
  int tens;
  int units;
  int sum_of_cubes;

  for (n = 100; n <= 999; n++) {
    // 1. 分解数字
    units = n % 10;
    tens = (n / 10) % 10;
    hundreds = n / 100;

    sum_of_cubes = (units * units * units) + (tens * tens * tens) +
                   (hundreds * hundreds * hundreds);
    if (sum_of_cubes == n)
      printf("%d\n", n);
  }
}

int main(void) {
  find_narcissistic_numbers();
  return 0;
}
