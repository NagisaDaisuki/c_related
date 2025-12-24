#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { PEACE, LEAP } YEAR_TYPE;

typedef struct DATE {
  YEAR_TYPE year;
  size_t month_2;
} DATE;

int main(void) {
  size_t year, month, day;
  DATE date = {};
  if (scanf("%zu,%zu,%zu", &year, &month, &day) != 3) {
    perror("year, month and day were not received correctly.\n");
    return EXIT_FAILURE;
  }

  if (year % 400 == 0 && year % 100 != 0 || year % 4 == 0) {
    date.year = LEAP;
    date.month_2 = 29;
  } else {
    date.year = PEACE;
    date.month_2 = 28;
  }

  for (int i = 1; i <= month; i++) {
    if (month != i) {
      if ((i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 ||
           i == 12))
        day += 31;
      else if (i == 2)
        day += date.month_2;
      else
        day += 30;
    }
  }
  printf("%zu\n", day);
  return 0;
}
