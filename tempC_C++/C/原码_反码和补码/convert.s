.section .data

input:  .asciz "1101"  # 原码输入
output: .asciz "%s\n"   # 格式化输出字符串

.section .bss

complement: .space 16   # 存储反码的缓冲区，长度为输入字符串长度加1
temp:       .space 16   # 临时缓冲区

.section .text
.globl main

main:
    # 将输入字符串地址传递给printf函数
    lea input, %rdi
    mov $0, %eax   # 清空eax寄存器

    # 调用printf输出原码
    call printf

    # 计算反码
    mov $0, %rbx   # ebx用于循环计数
loop_complement:
    movb input(%rbx), %al    # 读取input中的一个字符
    cmpb $0, %al             # 检查是否到达字符串结尾
    je end_complement        # 如果到达结尾，则结束循环

    # 将字符取反
    mov %al, temp(%rbx)       # 将字符存储到临时缓冲区
    xor $0x1, temp(%rbx)      # 取反操作
    inc %rbx                  # 循环计数加1
    jmp loop_complement       # 继续下一个字符的处理

end_complement:
    mov $0, %rbx  # 重置循环计数器

    # 输出反码
    lea temp, %rsi
    mov $0, %eax   # 清空eax寄存器
    call printf

    # 计算补码
    mov $0, %rbx   # 重置循环计数器
    mov $1, %rcx   # carry标志位

loop_add_one:
    movb temp(%rbx), %al    # 读取反码中的一个字符
    cmpb $0, %al             # 检查是否到达字符串结尾
    je end_add_one           # 如果到达结尾，则结束循环

    # 进行加1操作
    cmp $1, %rcx             # 检查carry标志位
    jne skip_carry           # 如果carry标志位为0，跳过进位操作
    add $1, %al              # 加1
    cmp $2, %al              # 检查是否溢出
    jae set_carry            # 如果溢出，设置carry标志位
    jmp skip_carry           # 否则跳过进位操作
set_carry:
    mov $1, %rcx             # 设置carry标志位为1
skip_carry:
    mov %al, temp(%rbx)      # 将字符存储到临时缓冲区
    inc %rbx                 # 循环计数加1
    jmp loop_add_one         # 继续下一个字符的处理

end_add_one:
    mov $0, %rbx  # 重置循环计数器

    # 输出补码
    lea temp, %rsi
    mov $0, %eax   # 清空eax寄存器
    call printf

    # 退出程序
    mov $0, %eax   # 返回值为0
    ret

