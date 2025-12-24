# 最终的可执行文件依赖于所有中间目标文件
hello: hello.o add.o sum.o sub.o mul.o
	gcc -o hello hello.o add.o sum.o sub.o mul.o

# 各个目标文件及其依赖关系

# hello.o 的编译规则
# 它依赖于其源文件和所有相关的头文件

hello.o: hello.c add.h sum.h sub.h mul.h head.h
	gcc -c hello.c -o hello.o

# 编译规则
# hello.o: hello.c add.h sum.h sub.h mul.h head.h 定义了 hello.o 的依赖项。
# 它不仅依赖于自己的源代码 hello.c，还依赖于它 #include 的所有头文件。
# 如果这些头文件中的任何一个被修改，make 就会知道需要重新编译 hello.c 
# 来更新 hello.o。
#
# 其他 .o 文件的规则也是同理，它们都明确地列出了自己的 
# .c 源文件和所有相关头文件的依赖。

# add.o 的编译规则
add.o: add.c add.h head.h
	gcc -c add.c -o add.o

# sum.o 的编译规则
sum.o: sum.c sum.h head.h
	gcc -c sum.c -o sum.o

# sub.o 的编译规则
sub.o: sub.c sub.h head.h
	gcc -c sub.c -o sub.o

# mul.o 的编译规则
mul.o: mul.c mul.h head.h
	gcc -c mul.c -o mul.o

# 清理规则
.PHONY: clean
clean:
	rm -f hello.o add.o sum.o sub.o mul.o hello
