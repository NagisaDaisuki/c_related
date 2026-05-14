#include <stdio.h>
#include <string.h>

int main(void) {
  char src[] = "Copy Me!";
  char dest[20];
  strcpy(dest, src);

  printf("1. [strcpy]\n");
  printf("  Source: \"%s\"\n", src);
  printf("  Dest: \"%s\"\n", dest);

  char dest_safe[5];
  const char *long_src = "HelloWorld!";

  strncpy(dest_safe, long_src, sizeof(dest_safe) - 1);
  dest_safe[sizeof(dest_safe) - 1] = '\0';

  printf("\n2. [strncpy]\n");
  printf("  Long Source: \"%s\"\n", long_src);
  printf("  Dest Safe (size 5): \"%s\"\n", dest_safe);
  // 演示如果不手动加 \0 会发生什么（仅逻辑说明，实际运行可能乱码）
  char bad_dest[5];
  strncpy(bad_dest, "Hello", 5);
  printf("%s", bad_dest); // 危险！bad_dest 没有 \0，printf
  // 会一直读内存直到崩溃或读到随机
  return 0;
}
