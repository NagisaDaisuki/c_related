#include <stdio.h>
#include <string.h>

int main(void) {
  char str[] = "This is a sample string";
  const char *delim = " ";
  char *token;

  // Get the first token
  token = strtok(str, delim);

  // Walk through other tokens
  while (token != NULL) {
    fprintf(stdout, "%s\n", token);
    token = strtok(NULL, delim);
  }
  return 0;
}
