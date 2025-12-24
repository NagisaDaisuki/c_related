#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

// 双指针法

char *is_palindrome(char *str, int size, char *buffer) {
  char *left = str;
  char *right = str + size - 1;
  while (left < right) {
    if (*left != *right || left == right)
      break;

    left++;
    right--;
  }

  if (left < right)
    strncpy(buffer, "No", 3);
  else
    strncpy(buffer, "Yes", 4);

  return buffer;
}

void remove_newline(char *s) {
  size_t len = strlen(s);
  if (len > 0 && s[len - 1] == '\n') {
    s[len - 1] = '\0';
  }
}

int main(void) {

  char str[MAX_LENGTH], buffer[MAX_LENGTH];
  memset(str, 0, MAX_LENGTH);

  if (fgets(str, MAX_LENGTH, stdin) == NULL) {
    perror("Failed to receive str.");
    return EXIT_FAILURE;
  }

  remove_newline(str);
  printf("%s\n", is_palindrome(str, strlen(str), buffer));
  return EXIT_SUCCESS;
}
