CC = gcc
CFLAGS = -Wall -g -std=gnu11 -O2 -Wextra 
LDFLAGS = -lncurses

TARGET = common_function

SRCS = .

C_SRCS = $(wildcard $(SRCS)/*.c)
C_OBJS = $(C_SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(C_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


$(SRCS)/%.o: $(SRCS)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(SRCS)/common_function.o: $(SRCS)/common_function.c

clean:
	rm -f $(TARGET) $(SRCS)/*.o

run:
	./$(TARGET)
