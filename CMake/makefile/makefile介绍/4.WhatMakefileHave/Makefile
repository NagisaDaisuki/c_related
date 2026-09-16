# Makefile里有什么？
# Makefile里主要包含了五个东西：显式规则、隐式规则、变量定义、指令和注释。

# 显式规则。显式规则说明了如何生成一个或多个目标文件。
# 这是由Makefile的书写者明显指出要生成的文件、文件的依赖文件和生成的命令。

# 隐式规则。由于我们的make有自动推导的功能，所以隐式规则可以让我们比较
# 简略地书写Makefile，这是由make所支持的。
 
# 变量的定义。在Makefile中我们要定义一系列的变量，变量一般都是字符串，
# 这个有点像你C语言中的宏，当Makefile被执行时，其中的变量都会被扩展到
# 相应的引用位置上。

# 指令。其包括了三个部分，一个是在一个Makefile中引用另一个Makefile，
# 就像C语言中的include一样；另一个是指根据某些情况指定Makefile中的有效部分，
# 就像C语言中的预编译#if一样；还有就是定义一个多行的命令。有关这一部分的
# 内容，我会在后续的部分中讲述。

# 注释。Makefile中只有行注释，和UNIX的Shell脚本一样，其注释是用 # 字符，
# 这个就像C/C++中的 // 一样。如果你要在你的Makefile中使用 # 字符，
# 可以用反斜杠进行转义，如： \# 。

# 最后，makefile中的命令必须要以 Tab 键开始。

ifndef CC
	CC = gcc
endif

ifndef CFLAGS
	CFLAGS = -Wall -g
endif

VAR1 = 1
VAR2 = 2

objects = hello.o add.o sum.o \
	sub.o mul.o
# 如果有新的 .o 文加入，我们只需简单地修改一下 objects 变量就可以了

headers = add.h sum.h sub.h mul.h \
	head.h

hello: $(objects) 
	gcc -o hello $(objects) 




# ----------------------------------------
# 使用 ifeq 控制不同代码执行
# ----------------------------------------
ifeq ($(VAR1), $(VAR2))

# 最终的可执行文件依赖于所有中间目标文件
# 各个目标文件及其依赖关系

# hello.o 的编译规则
# 它依赖于其源文件和所有相关的头文件

hello.o: hello.c $(headers)
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
# 不加 add.c, makefile 会自动推导你需要一个add.c文件编译中间文件
# gcc -c add.c -o add.o 这行命令也会被推导出来

add.o: $(headers)  # add.c $(headers)   # add.h head.h
#	gcc -c add.c -o add.o

# add.o: add.c $(headers)   # add.h head.h
#	gcc -c add.c -o add.o

# sum.o 的编译规则
sum.o: $(headers) # sum.c $(headers)  # sum.h head.h
#	gcc -c sum.c -o sum.o

# sub.o 的编译规则
sub.o: $(headers)  # sub.c $(headers)    # sub.h head.h
#	gcc -c sub.c -o sub.o

# mul.o 的编译规则
mul.o: $(headers)  # mul.c $(headers)  # mul.h head.h
#	gcc -c mul.c -o mul.o

# 清理规则
.PHONY: clean
clean:
	rm -f $(objects) hello







# ----------------------------------------
# 另一分支代码选择
# ----------------------------------------

else

# makefile 的另一种风格
# 许多重复的 .h 文件可以将其收拢如果几个 .c 文件都依赖一个 .h 文件

$(objects): head.h

hello.o: $(headers)

add.o: add.h
sum.o: sum.h
sub.o: sub.h
mul.o: mul.h

# 清理规则
.PHONY: clean
clean:
	@rm -rf $(objects) hello

endif
