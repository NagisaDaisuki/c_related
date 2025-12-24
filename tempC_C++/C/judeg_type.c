#include <ctype.h>
#include <stdio.h>

int main(void) {
  char ch;
  printf("Press a key and then press Enter:");
  ch = getchar();

  if (islower(ch))
    printf("It is an English character!");
  else if (isupper(ch))
    printf("It is an English character!");
  else if (isdigit(ch))
    printf("It is a digit character!");
  else if (isspace(ch))
    printf("It is a space character!");
  else
    printf("It is other character!");
  return 0;
}
