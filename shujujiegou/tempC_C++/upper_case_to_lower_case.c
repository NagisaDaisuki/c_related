#include <ctype.h>
#include <stdio.h>

int main(void) {
  char ch;
  printf("Press a key and then press enter:");
  scanf("%c", &ch);
  if (isupper(ch))
    printf("%c,%d", tolower(ch), tolower(ch));
  else
    printf("%c,%d", toupper(ch), toupper(ch));
  return 0;
}
