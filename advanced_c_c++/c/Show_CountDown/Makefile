# $@ : 左边的内容（实际生成的文件）
# $^ : 右边的内容 (所有依赖文件)
# $< : 右边的第一个内容 (第一个依赖文件)

# Makefile for Timer Project
# Builds both C and C++ versions

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Iinclude -Icommon -O2
CXXFLAGS = -Wall -Wextra -Iinclude -Icommon -O2
LDFLAGS = -lncurses

# Directories
SRC_C = src/c
SRC_CPP = src/cpp
COMMON = common

# Common objects 
COMMON_OBJ = $(COMMON)/color.o

# C targets
C_TARGET = timer-c
# C_SRCS = $(SRC_C)/main.c $(SRC_C)/timer.c $(SRC_C)/renderer.c
C_SRCS = $(wildcard $(SRC_C)/*.c)
C_OBJS = $(C_SRCS:.c=.o) # 通配符和后缀替换

# C++ targets
CPP_TARGET = timer-cpp
CPP_SRCS = $(wildcard $(SRC_CPP)/*.cpp)
CPP_OBJS = $(CPP_SRCS:.cpp=.o)

.PHONY: all clean install run-c run-cpp help

all: $(C_TARGET) $(CPP_TARGET)

# Build C version
$(C_TARGET): $(C_OBJS) $(COMMON_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_C)/%.o : $(SRC_C)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(SRC_C)/main.o: $(SRC_C)/main.c include/timer.h include/renderer.h
$(SRC_C)/timer.o: $(SRC_C)/timer.c include/timer.h
$(SRC_C)/renderer.o: $(SRC_C)/renderer.c include/renderer.h

# Build C++ versio
$(CPP_TARGET): $(CPP_OBJS) $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_CPP)/%.o: $(SRC_CPP)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRC_CPP)/main.o: $(SRC_CPP)/main.cpp include/timer.h include/renderer.h
$(SRC_CPP)/timer.o: $(SRC_CPP)/timer.cpp include/timer.hpp

# Common objects 
$(COMMON_OBJ): $(COMMON)/color.c include/color.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Run commands
run-c: $(C_TARGET)
	./$(C_TARGET) -m 30

run-cpp: $(CPP_TARGET)
	./$(CPP_TARGET) -m 30

# Clean
clean:
	rm -f $(C_TARGET) $(CPP_TARGET)
	rm -f $(C_OBJS) $(CPP_OBJS) $(COMMON_OBJ)
	# rm -f $(SRC_C)/*.o $(SRC_CPP)/*.o $(COMMON)/*.o

# Install to local bin
install: all
	install -Dm755 $(C_TARGET) ~/.local/bin/timer-c
	install -Dm755 $(CPP_TARGET) ~/.local/bin/timer-cpp

# Help
help:
	@echo "Timer Project - Makefile targets:"
	@echo "  all          - Build both C and C++ versions"
	@echo "  clean        - Remove built executables and objects"
	@echo "  run-c        - Run C version (30 min timer)"
	@echo "  run-cpp      - Run C++ version (30 min timer)"
	@echo "  install      - Install binaries to ~/.local/bin"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Options:"
	@echo "  -m <minutes> - Set timer duration"
	@echo "  -c <color>   - Set source color for matugen"

