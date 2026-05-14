#include <stdio.h>
#include <string.h>

int main(void) {
  const char *str1 = "Hello, C Language";
  size_t len1 = strlen(str1);

  printf("字符串：\"%s\"\n", str1);
  printf("strlen(str1)的结果（字符数）：%zu\n", len1);

  char str2[100] = "hello";

  printf("\n字符串：\"%s\"\n", str2);
  printf("sizeof(str2)（数组总大小）：%zu\n", sizeof(str2));
  printf("strlen(str2)（实际字符长）：%zu\n", strlen(str2));

  str2[2] = '\0';
  printf("\n修改 str[2] = '\\0' 后:\n");
  printf("字符串：\"%s\"\n", str2);
  printf("strlen(str2): %zu\n", strlen(str2));
  printf("sizeof(str2)（数组总大小）：%zu\n", sizeof(str2));

  return 0;
}
