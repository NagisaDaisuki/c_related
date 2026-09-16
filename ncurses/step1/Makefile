CC = gcc
CFLAGS = -Wall -g -std=c11 -O2 -Wextra
LDFLAGS = -lncurses

TARGET = hello_world

SRCS = .

C_SRCS = $(wildcard $(SRCS)/*.c)
C_OBJS = $(C_SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(C_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SRCS)/%.o: $(SRCS)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(SRCS)/hello_world.o: $(SRCS)/hello_world.c

clean:
	rm -f $(TARGET) $(SRCS)/*.o

run:
	./$(TARGET)
