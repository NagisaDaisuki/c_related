#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char a;
  int b;
  short c;
  char d;
} test;

typedef struct {
  char a;
  char d;
  short c;
  int b;
} test_optimized;

typedef struct {
  char a;
  double b;
  short c;
  char d;
} test2;

void test_function() {
  test a1 = {
      .a = 0x12,
      .b = 0x12345678,
      .c = 0x1234,
      .d = 0x34,
  };

  printf("结构体成员地址在内存中存放的位置：\n");
  printf("a的地址：%p\n", &a1.a);
  printf("b的地址：%p\n", &a1.b);
  printf("c的地址：%p\n", &a1.c);
  printf("d的地址：%p\n", &a1.d);
  // 按最大变量字节数对齐
  // sizeof(struct test)是 三个 int 类型变量大小之和 12字节
  printf("结构体test的总大小:");
  printf("%ld\n", sizeof(test));

  // 优化定义 test_optimized
  test_optimized a2 = {.a = 0x12, .d = 0x34, .c = 0x1234, .b = 0x12345678};

  printf("优化过的结构体test_optimized大小：");
  printf("%ld\n", sizeof(test_optimized));

  // 结构体test2 将 int类型改为double类型
  printf("test2结构体类型大小：");
  printf("%ld\n", sizeof(test2));

  // 机器是按照边界对齐方式存放变量
}

int main(void) {
  test_function();
  return 0;
}
