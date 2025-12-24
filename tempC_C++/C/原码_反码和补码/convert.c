#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 将字符串中的字符'0' 和 '1' 进行取反操作

void complement(char* binary)
{
  for(int i = 0;binary[i] != '\0';i++)
  {
    if(binary[i] == '0')
      binary[i] = '1';
    else if(binary[i] == '1')
      binary[i] = '0';
  }
}

// 将二进制字符串表示的补码加一

void add_one(char* binary)
{
  int carry = 1;
  for(int i = strlen(binary) - 1;i >= 0;i--)
  {
    if(binary[i] == '0' && carry == 1)
    {
      binary[i] = '1';
      carry = 0;
    }
    else if (binary[i] == '1' && carry == 1)
    {
      binary[i] = '0';
    }
  }
}

// 将原码转换为反码和补码

void convert_to_complement(char* binary)
{
    printf("原码: %s\n",binary);

    complement(binary);
    printf("反码: %s\n",binary);

    add_one(binary);
    printf("补码: %s\n",binary);
}

int main()
{
  char binary[100];
  
  printf("请输入原码的二进制表示(例如:1101): ");
  scanf("%s",binary);
  convert_to_complement(binary);
  return 0;
}
