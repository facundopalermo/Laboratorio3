CC = gcc
CFLAGS = -Wall -O1 -pthread -std=gnu89 -pedantic-errors
.PHONY: all
all: bingo


bingo: bingo.c bingo.h bingo_f.o
	$(CC) -o bingo bingo.c bingo_f.o $(CFLAGS)

bingo_f.o: bingo_f.c bingo.h
	$(CC) -c bingo_f.c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o
