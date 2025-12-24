#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_LENGTH 20

typedef struct Week_chart {
  int code;
  char date[DATE_LENGTH];
} date_table;

int main(void) {
  date_table table[7] = {
      {0, "Sunday"},   {1, "Monday"}, {0, "Tuesday"},  {0, "Wednesday"},
      {0, "Thursday"}, {0, "Friday"}, {0, "Saturday"},
  }; // 结构体数组内存储的字符串没有'\n' 而 fgets获取的字符串有'\n'

  char str[DATE_LENGTH];
  memset(str, 0, sizeof(str));

  if (fgets(str, DATE_LENGTH, stdin) == NULL) {
    perror("Error while input date.");
    return EXIT_FAILURE;
  }

  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n')
    str[len - 1] = '\0';

  int i;
  for (i = 0; i < 7; i++) {
    if (strcmp(table[i].date, str) == 0)
      break;
  }
  if (i < 7)
    printf("%s %d", str, i);
  else
    printf("not found");
  return 0;
}
