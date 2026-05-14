#include <stdio.h>
#include <stdlib.h>

#define LENGTH 200

int string_length(char str[]) {
  int i, counter;
  for (i = 0; str[i] != '\0'; i++) {
    counter++;
  }
  return counter;
}

int main(void) {
  int j;
  char str[LENGTH] = {};
  if (fgets(str, LENGTH, stdin) != NULL) {
    for (j = string_length(str) - 1; j >= 0; j--) {
      putchar(str[j]);
    }
    printf("\n");
  }
  return 0;
}
