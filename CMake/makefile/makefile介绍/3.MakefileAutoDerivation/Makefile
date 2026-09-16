# GNU的make很强大，它可以自动推导文件以及文件依赖关系后面的命令，
# 于是我们就没必要去在每一个 .o 文件后都写上类似的命令，
# 因为，我们的make会自动识别，并自己推导命令。

# 只要make看到一个 .o 文件，它就会自动的把 .c 文件加在依赖关系中，
# 如果make找到一个 whatever.o ，那么 whatever.c 就会是 whatever.o 的依赖文件。
# 并且 cc -c whatever.c 也会被推导出来，于是，我们的makefile再也不用写得这么复杂。
# 我们的新makefile又出炉了。


# 使用 ifdef 和 ifndef 设置变量
# 使用 ifeq 和 ifneq 设置不同代码执行

ifndef CC
	CC = gcc
endif

ifndef CFLAGS
	CFLAGS = -Wall -g
endif

VAR1 = 1
VAR2 = 2

# 在工程复杂时使用变量更易于维护

# 将所有中间目标文件用变量囊括
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
