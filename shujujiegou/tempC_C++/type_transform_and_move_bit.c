#include <stdio.h>
#include <stdlib.h>

void test1() {
  short int a = -12345;
  int a1 = (int)a;
  unsigned short int a2 = (unsigned short int)a;
  unsigned int a3 = (unsigned int)a;
  fprintf(stdout, "Original: ");
  fprintf(stdout, "%hd 0x%hx\n", a, a);
  fprintf(stdout, "To int: ");
  fprintf(stdout, "%d 0x%x\n", a1, a1);
  fprintf(stdout, "To unsigned short: ");
  fprintf(stdout, "%hu 0x%hx\n", a2, a2);
  fprintf(stdout, "To unsigned int: ");
  fprintf(stdout, "%u 0x%x\n", a3, a3);
}

void test2() {
  int a = 2147483647;
  short int a1 = (short int)a;
  unsigned short int a2 = (unsigned short int)a;
  float a3 = (float)a;

  fprintf(stdout, "Original: ");
  fprintf(stdout, "%d 0x%x\n", a, a);
  fprintf(stdout, "To short: ");
  fprintf(stdout, "%hd 0x%hx\n", a1, a1);
  fprintf(stdout, "To unsigned short: ");
  fprintf(stdout, "%hu 0x%hx\n", a2, a2);
  fprintf(stdout, "To float: ");
  fprintf(stdout, "%f 0x%x\n", a3, *(unsigned int *)&a3);
}
void test3() {
  float a = 123456.789e5;
  double a1 = (double)a;

  fprintf(stdout, "Original: ");
  fprintf(stdout, "%f 0x%x\n", a, *(unsigned int *)&a);
  fprintf(stdout, "To double: ");
  fprintf(stdout, "%lf 0x%llx\n", a1, *(unsigned long long *)&a1);
}
void test4() {
  short int a = -12345;

  fprintf(stdout, "Original: ");
  fprintf(stdout, "%hd %hd %hd\n", (short int)(a << 1), (short int)(a << 2),
          (short int)(a >> 1));
  fprintf(stdout, "left move 1 bit, left move 2 bit, right move 1 bit: ");
  fprintf(stdout, "0x%hx 0x%hx 0x%hx\n", a << 1, a << 2, a >> 1);
}
void test5() {
  unsigned short int a = 53191;
  fprintf(stdout, "Original: ");
  fprintf(stdout, "%hu %hu %hu\n", (unsigned short int)(a << 1),
          (unsigned short int)(a << 2), (unsigned short int)(a >> 1));
  fprintf(stdout, "left move 1 bit, left move 2 bit, right move 1 bit: ");
  fprintf(stdout, "0x%hx 0x%hx 0x%hx\n", a << 1, a << 2, a >> 1);
}

int main(void) {
  puts("=======================================================");
  test1();
  puts("=======================================================");
  test2();
  puts("=======================================================");
  test3();
  puts("=======================================================");
  test4();
  puts("=======================================================");
  test5();
  puts("=======================================================");
  return 0;
}
