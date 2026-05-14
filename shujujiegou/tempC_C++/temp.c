#include <stdio.h>
#include <string.h>

char const *keyword[] = {"do",     "for",   "register", "return",
                         "switch", "while", NULL};
// 在指针数组末尾添加NULL作为数组遍历结束符
#define N_KEYWORD

int lookup_keyword(char const *const desired_word, char const *keyword_table[],
                   int const size) {
  char const **kwp;

  // 对于表中的每个单词
  for (kwp = keyword_table; *kwp != NULL; kwp++)
    if (strcmp(desired_word, *kwp) == 0)
      return kwp - keyword_table;
  // 如果没有找到
  return -1;
}

int main(void) {
  int array[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
  int *p;
  int size = sizeof(array) / sizeof(array[0]);

  for (p = array; p < array + size; p++)
    printf("%d\n", *p);

  printf("\n#=============================================");
  int move_vol =
      lookup_keyword("do", keyword, sizeof(keyword) / sizeof(keyword[0]));
  printf("\nmove_vol = %d\n", move_vol);
  return 0;
}
