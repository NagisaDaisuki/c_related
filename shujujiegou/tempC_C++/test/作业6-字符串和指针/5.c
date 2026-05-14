#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 80

char *my_strncat(char *dest, const char *src, size_t n) {
  char *p = dest;

  // 1. 找到目标字符串 dest 的末尾(即找到 '\0' 结束符)
  // p 移动到 dest 的结束符位置

  while (*p != '\0') {
    p++;
  }

  // 2. 从源字符串 src 中复制最多 n 个字符
  for (size_t i = 0; i < n; i++) {
    // 检查源字符串是否已经结束
    if (*src == '\0')
      break;
    // 复制字符
    *p = *src;

    // 移动到下一个位置
    p++;
    src++;
  }

  // 3. 在目标字符串的末尾添加新的结束符 '\0'
  *p = '\0';

  // 4. 返回目标字符串的起始位置
  return dest;
}

void remove_newline(char *s) {
  size_t len = strlen(s);
  if (len > 0 && s[len - 1] == '\n') {
    s[len - 1] = '\0';
  }
}

int main(void) {
  char str1[LENGTH], str2[LENGTH];

  // 给两个数组的所有位置零
  memset(str1, 0, sizeof(str1));
  memset(str2, 0, sizeof(str2));

  if (fgets(str1, LENGTH, stdin) == NULL) {
    perror("Error while input str1.");
    return EXIT_FAILURE;
  }
  if (fgets(str2, LENGTH, stdin) == NULL) {
    perror("Error while input str2");
    return EXIT_FAILURE;
  }

  // 使用fgets接收字符串后需要把最后的'\n'符号移除
  remove_newline(str1);
  remove_newline(str2);
  my_strncat(str1, str2, 5);

  fputs(str1, stdout);

  return 0;
}
