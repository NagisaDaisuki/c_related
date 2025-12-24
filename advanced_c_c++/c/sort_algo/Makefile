CC=gcc
CFLAGS=-Wall -g -std=gnu11 -O2 -lm -Wextra

all: sort

sort: main.o sort.o
	$(CC) $(CFLAGS) -o sort main.o sort.o

main.o: main.c sort.h
	$(CC) $(CFLAGS) -c main.c

sort.o: sort.c sort.h
	$(CC) $(CFLAGS) -c sort.c

clean: 
	rm -f sort *.o
