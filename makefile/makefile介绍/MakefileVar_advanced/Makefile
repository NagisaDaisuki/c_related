# 使用通配符和变量
# 项目目录结构
#.
#├── Makefile
#├── src/
#│   ├── hello.c
#│   ├── add.c
#│   └── sub.c
#│   └── sum.c
#│   └── mul.c
#└── include/
#    ├── hello.h
#    ├── add.h
#    └── sub.h
#    └── sum.h
#    └── mul.h
#    └── head.h

# 定义编译器和编译选项
CC = gcc
CFLAGS = -Wall -g

# 定义源代码和目标文件的目录
# 变量名 = 文件夹名

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj # 专门存放目标文件的目录

# 使用 wildcards 函数获取指定目录下的所有 .c 文件
# wildcards 会在指定目录中找到所有匹配模式的文件

SRCS = $(wildcard $(SRC_DIR)/*.c)
# SRCS = $(wildcard $(SRC_DIR)/*.c)
# equals to
# SRCS = src/hello.c src/add.c src/sub.c src/sum.c src/mul.c

# 使用 patsubst 函数生成对应的 .o 目标文件路径
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# 最终可执行文件
TARGET = Calc_program

# ---- Rules ----
.PHONY: all clean

# Main target to link all object files
all: $(TARGET)

# 默认目标：链接所有目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# 通用编译规则：将src/ 目录下的 .c 文件编译到 obj/ 目录下
# 依赖于源文件本身和所有头文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# 自动生成头文件依赖关系
-include $(OBJS:.o=.d)

# 编译依赖生成规则
$(OBJS:.o=.d): $(SRC_DIR)/%.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) -I$(INC_DIR) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ >> $@; \
	rm -f $@.$$$$

# 清理规则
clean:
	@rm -rf $(OBJ_DIR) $(TARGET)
