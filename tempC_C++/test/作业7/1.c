#include <stdio.h>

#define LENGTH 12

int main(void) {
  char *month[LENGTH] = {
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December",
  };
  // memset(month, NULL, sizeof(month));
  unsigned short int p = 0;
  if (fscanf(stdin, "%hu", &p) != 1)
    return -1;

  switch (p) {
  case 1:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 2:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 3:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 4:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 5:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 6:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 7:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 8:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 9:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 10:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 11:
    printf("%d %s\n", p, month[p - 1]);
    break;
  case 12:
    printf("%d %s\n", p, month[p - 1]);
    break;
  default:
    printf("illegal month\n");
    break;
  }

  return 0;
}
