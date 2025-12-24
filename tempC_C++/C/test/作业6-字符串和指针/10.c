#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_calendar(int months[], int day);

int main(void) {
  int months_peace[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int months_leap[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  size_t year, day;
  if (scanf("%zu,%zu", &year, &day) != 2) {
    fprintf(stdout, "year and day were not received correctly.");
    // return EXIT_FAILURE;
  }

  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    print_calendar(months_leap, day);
  else
    print_calendar(months_peace, day);

  return 0;
}

void print_calendar(int months[], int day) {
  int month = 1;
  for (int i = 1; day - months[i] > 0; i++) {
    day -= months[i];
    month++;
  }
  printf("%d,%d\n", month, day);
}
