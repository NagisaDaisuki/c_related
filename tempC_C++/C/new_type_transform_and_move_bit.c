#include <math.h> // 虽然没有直接用到数学函数，但通常与浮点数一起包含
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 确保在 64 位系统上 ULL 是 64 位
typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;

// =======================================================
// (1) short -12345 转换为 int, unsigned short, unsigned int
void test1() {
  short int a = -12345;
  int a1 = (int)a;
  unsigned short int a2 = (unsigned short int)a;
  unsigned int a3 = (unsigned int)a;

  // Original: -12345 (0xCFC7, 假设 16位 short)
  fprintf(stdout, "(1) short -12345 转换:\n");
  fprintf(stdout, "Original: %hd (0x%hx)\n", a, a);

  // 符号扩展到 int (例如 32位: 0xFFFFCFC7)
  fprintf(stdout, "To int: %d (0x%x)\n", a1, a1);

  // 截断到 unsigned short (0xCFC7)
  fprintf(stdout, "To unsigned short: %hu (0x%hx)\n", a2, a2);

  // 符号扩展到 int, 再转换为 unsigned int (0xFFFFCFC7)
  fprintf(stdout, "To unsigned int: %u (0x%x)\n", a3, a3);
}

// =======================================================
// (2) int 2147483647 转换为 short, unsigned short, float
void test2() {
  int a = 2147483647; // 0x7FFFFFFF (INT_MAX)
  short int a1 = (short int)a;
  unsigned short int a2 = (unsigned short int)a;
  float a3 = (float)a;

  fprintf(stdout, "\n(2) int 2147483647 转换:\n");
  fprintf(stdout, "Original: %d (0x%x)\n", a, a);

  // 截断到 short (0xFFFF, -1)
  fprintf(stdout, "To short: %hd (0x%hx)\n", a1, a1);

  // 截断到 unsigned short (0xFFFF, 65535)
  fprintf(stdout, "To unsigned short: %hu (0x%hx)\n", a2, a2);

  // 转换为 float (会发生精度丢失，变为 2147483648.0)
  // 打印 float 的十六进制需要用指针转换
  fprintf(stdout, "To float: %f (0x%x)\n", a3, *(uint32_t *)&a3);
}

// =======================================================
// (3) float 123456.789e5 转换为 double
void test3() {
  float a = 123456.789e5; // 12345678.9
  double a1 = (double)a;

  fprintf(stdout, "\n(3) float 123456.789e5 转换为 double:\n");
  // 打印 float 的十六进制
  fprintf(stdout, "Original (float): %f (0x%x)\n", a, *(uint32_t *)&a);

  // 打印 double 的十六进制需要用指针转换到 unsigned long long (uint64_t)
  fprintf(stdout, "To double: %lf (0x%llx)\n", a1, *(uint64_t *)&a1);
}

// =======================================================
// (4) short -12345 的位移操作
void test4() {
  short int a = -12345;

  // 修正: 位移结果是 int，这里显式转换回 short，以符合打印格式
  short int a_l1 = (short int)(a << 1);
  short int a_l2 = (short int)(a << 2);
  short int a_r1 = a >> 1; // 符号位会扩展 (算术右移)

  fprintf(stdout, "\n(4) short -12345 的位移:\n");
  fprintf(stdout, "Original: %hd (0x%hx)\n", a, a);

  fprintf(stdout, "Result: %hd (0x%hx), %hd (0x%hx), %hd (0x%hx)\n", a_l1, a_l2,
          a_r1, a_l1, a_l2, a_r1);
}

// =======================================================
// (5) unsigned short 53191 的位移操作
void test5() {
  unsigned short int a = 53191; // 0xCFC7

  // 修正: 确保结果被截断回 unsigned short，因为位移操作的结果是 int
  unsigned short int a_l1 = (unsigned short int)(a << 1);
  unsigned short int a_l2 = (unsigned short int)(a << 2);
  unsigned short int a_r1 = a >> 1; // 逻辑右移

  fprintf(stdout, "\n(5) unsigned short 53191 的位移:\n");
  fprintf(stdout, "Original: %hu (0x%hx)\n", a, a);

  fprintf(stdout, "Result: %hu (0x%hx), %hu (0x%hx), %hu (0x%hx)\n", a_l1, a_l2,
          a_r1, a_l1, a_l2, a_r1);
}

int main(void) {
  // puts("=======================================================");
  // test1();
  // puts("=======================================================");
  // test2();
  // puts("=======================================================");
  // test3();
  // puts("=======================================================");
  // test4();
  // puts("=======================================================");
  test5();
  // puts("=======================================================");
  return 0;
}
