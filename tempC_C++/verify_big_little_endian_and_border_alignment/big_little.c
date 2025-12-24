#include <stdio.h>

typedef enum {
  ENDIAN_UNKNOWN = 0,
  ENDIAN_LITTLE = 1,
  ENDIAN_BIG = 2,
} EndianType;

// 检测当前系统的大小端模式
EndianType check_endianness() {
  union {
    unsigned int i;
    unsigned char c[4];
  } b;

  b.i = 0x12345678;
  // 0x12 是高字节(MSB), 0x78 是低字节(LSB)

  // 如果低地址 b.c[0] 存的是 0x78 则是 小端
  if (b.c[0] == 0x78 && b.c[1] == 0x56 && b.c[2] == 0x34 && b.c[3] == 0x12)
    return ENDIAN_LITTLE;
  else if (b.c[0] == 0x12 && b.c[1] == 0x34 && b.c[2] == 0x56 && b.c[3] == 0x78)
    return ENDIAN_BIG;

  return ENDIAN_UNKNOWN;
}

int main(void) {
  printf("=======================================\n\n");
  printf("大小端模式测试:\n");
  printf("该机器是%s机器\n",
         (check_endianness() == ENDIAN_LITTLE) ? "小端" : "大端");
  printf("\n\n=======================================");
  return 0;
}
