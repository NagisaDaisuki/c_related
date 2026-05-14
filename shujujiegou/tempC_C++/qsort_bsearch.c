#include <stdio.h>
#include <stdlib.h>

static int my_strcmp(const char *s1, const char *s2);

static int my_strlen(const char *a);

int main(void) { return 0; }

static int my_strcmp(const char *s1, const char *s2) {

  while (*s1 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
  }
  // 为什么强制转换为 unsigned char？
  // C 语言标准规定 strcmp 比较时应将字符视为 unsigned char。
  // 如果不转，对于扩展 ASCII 码（如大于 127 的字符），
  // 可能会被当成负数，导致比较结果错误。
  return *(unsigned char *)s1 - *(unsigned char *)s2;
}

static int my_strlen(const char *a) {
  const char *p = a;
  while (*p != '\0')
    p++;
  return p - a;
}
