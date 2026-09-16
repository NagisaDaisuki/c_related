# 编译器 与 参数
CXX = g++
DEPFLAGS = -MMD -MP # -MMD 是用来生成 .d (dependency)依赖文件的开关，加上它
										# 就会在编译出 .o 文件的同时在旁边顺手生成一个同名的 .d 文件
										# -MP 是 Make Phony 的 缩写，如果那天删除了一个不再使用的 .hpp 文件 
										#  如果没有这个 参数，Make 会因为在旧的 .d 文件里找不到那个头文件而当场报错罢工
										#  加上 -MP 编译器会給每个头文件生成一个空的 伪目标，完美避免这种令人抓狂的连环报错
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -Iinclude $(DEPFLAGS)

# 目标结构
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/LinearListTest

# 文件抓取
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS)) # patsubst 比:.cpp=.o更高级
																															 # 模式替换把 src/main.cpp 精准
																															 # 替换为 build/main.o
																															 # 避免在.cpp旁生成一堆 .o文件
																															 # 在build内也好clean
DEPS = $(OBJS:.o=.d)

# 默认规则
.PHONY: all clean run

all: $(TARGET)

# 链接可执行文件
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 编译成 .o 对象文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# 运行测试
run: $(TARGET)
	./$(TARGET)

# 清理产物
clean:
	rm -rf $(BUILD_DIR)

# 及其关键：引物生成的 .d 依赖文件
-include $(DEPS)
