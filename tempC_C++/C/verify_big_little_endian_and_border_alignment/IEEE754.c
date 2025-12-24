#include <stdio.h>
#include <string.h>

// 定义一个辅助函数，用于打印一个字节的8位二进制
void print_byte_as_binary(unsigned char byte) {
  for (int i = 7; i >= 0; i--) {
    // (byte >> i) & 1 意思把第i位移到最后，然后和1做与运算取值
    printf("%d", (byte >> i) & 1);
  }
}

int main(void) {
  // 1. 定义浮点数
  float fval = 12345.0f;

  // 2. 获取该变量在内存中的起始地址
  // 关键点：将 float* 强制转换为 unsigned char*,
  // 这样我们可以一个字节一个字节地看
  unsigned char *p = (unsigned char *)&fval;

  printf("浮点数值：%f\n", fval);
  printf("变量大小：%zu 字节\n", sizeof(float));
  printf("-----------------------------------\n");

  // 3. 按照 内存物理地址 顺序打印（模拟书上的show_bytes）
  // 这种方式展示了数据在内存条里到底是怎么躺着的
  printf("【内存物理视图（由低地址 -> 高地址）】：\n");
  printf("地址偏移\t十六进制\t二进制\n");

  for (int i = 0; i < sizeof(float); i++) {
    printf("字节%d： \t0x%02X \t", i, p[i]);
    print_byte_as_binary(p[i]);
    printf("\n");
  }
  printf("-----------------------------------\n");

  // 4. 按照【IEEE 754逻辑视图】打印（将内存作为一个整体读取）
  // 这里将4个字节视为一个32位整数读取，并在打印时调整为大端序阅读习惯
  // 这样就能看到书上计算出来的 46 40 E4 00
  unsigned *int_view = (unsigned int *)&fval;
  unsigned int val = *int_view;

  printf("【IEEE 754逻辑视图（人类阅读习惯/大端）】：\n");
  printf("整体十六进制值：0x%08X\n\n", val);

  printf("拆解分析：\n");

  return 0;
}
