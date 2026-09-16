CXX = g++
DEPFLAGS = -MMD -MP
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -g -Iinclude $(DEPFLAGS)

# 目标结构
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/LinearListTest

# 文件抓取
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
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
