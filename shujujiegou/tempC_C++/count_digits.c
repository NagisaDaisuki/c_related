#include <stdio.h>
#include <limits.h>

// 函数：计算一个非负长整型数的位数
int count_digits(long n) {
    // 如果数字是0，则位数为1
    if (n == 0) {
        return 1;
    }

    int count = 0;
    // 当n大于0时，循环执行
    while (n > 0) {
        n /= 10;  // n除以10
        count++;  // 计数器加1
    }
    return count;
}

int main() {
    long number;

    printf("请输入一个范围在 0 到 %ld 之间的正整数: ", LONG_MAX);
    if (scanf("%ld", &number) == 1) {
        if (number < 0) {
            printf("错误：请输入一个非负整数。\n");
        } else {
            int digits = count_digits(number);
            printf("数字 %ld 的位数是: %d\n", number, digits);
        }
    } else {
        printf("无效的输入。\n");
    }

    return 0;
}

