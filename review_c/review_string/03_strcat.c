#include <stdio.h>
#include <string.h>

int main() {
    // 1. strcat (String Concatenate)
    // 原型: char *strcat(char *dest, const char *src);
    // 作用: 把 src 接到 dest 的后面。
    // *风险*: 极其危险！如果 dest 空间不够，会直接覆盖后面的内存。

    // 必须预留足够的空间！
    // 错误写法: char dest[] = "Hello"; (空间固定为 6，没法再加了)
    char dest[50] = "Hello"; 
    const char *src = ", World!";

    printf("1. [strcat]\n");
    printf("   Before: \"%s\"\n", dest);
    strcat(dest, src);
    printf("   After:  \"%s\"\n", dest);

    // 2. strncat (带限制的拼接)
    // 原型: char *strncat(char *dest, const char *src, size_t n);
    // 作用: 把 src 的前 n 个字符接到 dest 后面。
    // *良心设计*: strncat 即使截断了，也会自动在最后补上 '\0'。

    char dest2[20] = "Log_";
    const char *message = "Error: System Failure 404";

    // 计算还能塞多少字符
    // 总大小 20 - 当前长度 4 - 结尾符 1 = 15
    size_t current_len = strlen(dest2);
    size_t available_space = sizeof(dest2) - current_len - 1;

    printf("\n2. [strncat]\n");
    printf("   Before: \"%s\"\n", dest2);
    
    // 只拼接剩余空间允许的长度
    strncat(dest2, message, available_space);

    printf("   Source: \"%s\"\n", message);
    printf("   After:  \"%s\"\n", dest2);
    printf("   Len:    %zu\n", strlen(dest2));

    return 0;
}
