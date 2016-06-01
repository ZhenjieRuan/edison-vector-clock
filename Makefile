CC=gcc
CFLAGS=-Wall -I./include -o

all: src/vector_clock.c
	$(CC) $(CFLAGS) vector_clock $^ 

clean:
	rm vector_clock
