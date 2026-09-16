CC = gcc
CFLAGS = -Wall -g

vpath %.c src
vpath %.h include

SRC_DIR = src
HDR_DIR = include
OBJ_DIR = obj

SRCS := $(wildcard SRC_DIR/%.c)
HDRS := $(wildcard HDR_DIR/%.h)
OBJS := $(patsubst SRC_DIR/%.c,OBJ_DIR/%o,$(SRCS))


TARGET = hello

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o %@ %<

$(OBJS)/%.o: %.c $(HDRS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(dir $(HDRS))  -c $< -o $@

DEPS := $(OBJS: .o=.d)

-include $(DEPS)

$(OBJ_DIR)/%.d: %.c
	@set -e; rm -f $@; \
	
