#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mergeAlternately(char *word1, char *word2) {
  char *word_ptr1 = word1;
  char *word_ptr2 = word2;

  int word1_len = 0;
  int word2_len = 0;
  for (; *word_ptr1++ != '\0';)
    word1_len++;
  for (; *word_ptr2++ != '\0';)
    word2_len++;
  /*
   *  word1_len = strlen(word1);
   *  word2_len = strlen(word2);
   * */

  // printf("%d %d\n", word1_len, word2_len);
  word_ptr1 = word1;
  word_ptr2 = word2;

  char *result = malloc(word1_len + word2_len + 1); // +1 是字符串结束标识符
  char *temp_result = result;
  while (*word_ptr1 != '\0' || *word_ptr2 != '\0') {
    if (*word_ptr1 != '\0')
      *temp_result++ = *word_ptr1++;
    if (*word_ptr2 != '\0')
      *temp_result++ = *word_ptr2++;
  }
  *temp_result = '\0';
  fputs(result, stdout);
  printf("\n");
  return result;
}

int main(void) {
  char *word1 = "string";
  char *word2 = "literal";

  fprintf(stdout, "%s\n", mergeAlternately(word1, word2));
  return 0;
}
