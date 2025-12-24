#include <stdio.h>
#include <stdlib.h>

int main() {
  char data[5];

  // 错误操作：数组只有5个字节，但写入了6个字符，没有留空间给 '\0'
  // 实际上是写入了 'H', 'e', 'l', 'l', 'o'，'\0' 溢出到了 data 之外
  // 但在这个例子中，我们假设用 memcpy 或其它方式精确地填满 data，没有 \0
  data[0] = 'A';
  data[1] = 'B';
  data[2] = 'C';
  data[3] = 'D';
  data[4] = 'E'; // <--- 数组已满，没有空终止符

  printf("尝试写入一个非终止字符串...\n");

  // fputs 将会从 data[0] 开始一直读到内存中找到 \0 为止
  // 这将是 UB！
  // fputs(data, stdout);
  if (fputs(data, stdout) == EOF) {
    // 错误
    if (ferror(stdout)) {
      perror("failed to write stdout.");
      exit(EXIT_FAILURE);
    }
  }

  // printf("\n程序可能崩溃，或者输出了乱码。\n");

  return 0;
}
