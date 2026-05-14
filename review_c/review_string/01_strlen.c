#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {

  // 1. 基本用法
  const char *str1 = "Hello, C Language!";
  size_t len1 = strlen(str1);

  printf("字符串: \"%s\"\n", str1);
  printf("strlen(str1) 的结果 (字符数): %zu\n", len1);

  // 2. strlen vs sizeof
  // sizeof 计算的是数组分配的内存大小（包含结尾的 \0）
  // strlen 计算的是有效字符的长度（遇到 \0 停止，不包含 \0）
  char str2[100] = "Hello";

  printf("\n字符串: \"%s\"\n", str2);
  printf("sizeof(str2)  (数组总大小): %zu\n", sizeof(str2));
  printf("strlen(str2)  (实际字符长): %zu\n", strlen(str2));

  // 3. 手动修改 \0 的位置
  str2[2] = '\0'; // 在 'l' 的位置截断
  printf("\n修改 str2[2] = '\\0' 后:\n");
  printf("字符串: \"%s\"\n", str2);
  printf("strlen(str2): %zu\n", strlen(str2));

  return 0;
}
