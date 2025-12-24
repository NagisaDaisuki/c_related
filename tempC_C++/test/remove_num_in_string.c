#include <stdio.h>
#define LENGTH 20

void remove_num_in_str(char *str);

void remove_num(char *str);

int main(void) {

  char str[LENGTH] = "1myu23wuli47kaka";
  // memset(str, 0, sizeof(str));
  fprintf(stdout, "before remove: %s\n", str);
  remove_num(str);
  fprintf(stdout, "after remove: %s\n", str);
  return 0;
}

// 双指针时间复杂度(N)
void remove_num(char *str) {
  if (str == NULL) {
    return;
  }

  // write_ptr 指向下一个要写入的有效位置（慢指针）
  char *write_ptr = str;

  // read_ptr 遍历整个原始字符串（快指针）
  char *read_ptr = str;

  // 当快指针还没有到达字符串末尾时，持续前进
  while (*write_ptr != '\0') {

    // 1. 判断当前字符是不是数字
    if (*read_ptr >= '0' && *read_ptr <= '9') {
      // 是数字：我们跳过它！
      // 只需要让 read_ptr 往前走一步，write_ptr 保持不动(覆盖掉这个数字)
    } else {
      // 2. 不是数字：这是有效字符，需要保留
      // 将 read_ptr 指向的字符拷贝到 write_ptr 指向的位置
      // 只有当两个指针指向不同位置时才需要拷贝
      if (write_ptr != read_ptr)
        *write_ptr = *read_ptr;

      // write_ptr 向前走一步，为下一个有效字符腾出位置
      write_ptr++;
    }

    // 无论是否是数字，快指针 read_ptr都要往前走一步，检查下一个字符;
    read_ptr++;
  }

  *write_ptr = '\0';
}

// 时间复杂度(N * N)
void remove_num_in_str(char *str) {

  char *str_ptr, *str_ptr1;

  for (str_ptr = str; *str_ptr != '\0'; str_ptr++) {
    if (*str_ptr >= '0' && *str_ptr <= '9') {
      for (str_ptr1 = str_ptr + 1; *str_ptr1 != '\0'; str_ptr1++) {
        *(str_ptr1 - 1) = *str_ptr1;
      }
      *(str_ptr1 - 1) = '\0';
      str_ptr--;
    }
  }
}
