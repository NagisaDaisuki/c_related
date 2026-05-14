#include <stdio.h>
#include <string.h>

int main() {
    // 1. strcpy (String Copy)
    // 原型: char *strcpy(char *dest, const char *src);
    // 作用: 把 src 指向的字符串复制到 dest，包含 '\0'。
    
    char src[] = "Copy Me!";
    char dest[20]; // 必须确保 dest 足够大，否则缓冲区溢出 (Buffer Overflow)

    strcpy(dest, src);
    
    printf("1. [strcpy]\n");
    printf("   Source: \"%s\"\n", src);
    printf("   Dest:   \"%s\"\n", dest);

    // 2. strncpy (Safe String Copy - sort of)
    // 原型: char *strncpy(char *dest, const char *src, size_t n);
    // 作用: 最多复制 n 个字符。
    // *陷阱*: 如果 src 的长度 >= n，strncpy 不会在 dest 末尾加 '\0'！
    
    char dest_safe[5]; // 假设空间很小
    const char *long_src = "HelloWorld";
    
    // 我们只想复制前 4 个字符，留 1 个位置给 '\0'
    strncpy(dest_safe, long_src, sizeof(dest_safe) - 1);
    
    // *必须手动添加结束符*，这是使用 strncpy 的黄金法则
    dest_safe[sizeof(dest_safe) - 1] = '\0'; 

    printf("\n2. [strncpy]\n");
    printf("   Long Source: \"%s\"\n", long_src);
    printf("   Dest Safe (size 5): \"%s\"\n", dest_safe);

    // 演示如果不手动加 \0 会发生什么（仅逻辑说明，实际运行可能乱码）
    // char bad_dest[5];
    // strncpy(bad_dest, "Hello", 5);
    // printf("%s", bad_dest); // 危险！bad_dest 没有 \0，printf 会一直读内存直到崩溃或读到随机 0

    return 0;
}
