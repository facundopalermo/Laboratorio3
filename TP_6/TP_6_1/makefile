CC = gcc
CFLAGS = -Wall -O1 -pthread -std=gnu89 -pedantic-errors
.PHONY: all
all: pienso


pienso: pienso.c pienso.h pienso_f.o
	$(CC) -o pienso pienso.c pienso_f.o $(CFLAGS)

pienso_f.o: pienso_f.c pienso.h
	$(CC) -c pienso_f.c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o