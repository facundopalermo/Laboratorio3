# Crea los programas

CC = gcc
FG = -Wall -O1 -std=gnu89 -pedantic-errors -Werror
FGT = $(FG) -pthread

COMMON_ROUTE = ../common/
HEADERS_COMMON = -I$(COMMON_ROUTE)

.PHONY: all
all: vendedor pizzero

vendedor: ../vendedor.c vendedor_f.o global.o semaforo.o mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FGT) -o vendedor ../vendedor.c vendedor_f.o global.o semaforo.o mensaje.o threads.o clave_recurso.o memcomp.o

vendedor_f.o: ../vendedor_f.c ../vendedor_f.h global.o semaforo.o mensaje.o memcomp.o 
	$(CC) $(FG) -c ../vendedor_f.c

pizzero: ../pizzero.c pizzero_f.o global.o semaforo.o mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FGT) -o pizzero ../pizzero.c pizzero_f.o global.o semaforo.o mensaje.o threads.o clave_recurso.o memcomp.o

pizzero_f.o: ../pizzero_f.c ../pizzero_f.h global.o semaforo.o mensaje.o memcomp.o threads.o
	$(CC) $(FG) -c ../pizzero_f.c

global.o: $(COMMON_ROUTE)global.c $(COMMON_ROUTE)global.h
	$(CC) $(FG) -c $(COMMON_ROUTE)global.c $(HEADERS_COMMON)

threads.o: $(COMMON_ROUTE)threads.c $(COMMON_ROUTE)threads.h
	$(CC) $(FG) -c $(COMMON_ROUTE)threads.c $(HEADERS_COMMON)

semaforo.o: clave_recurso.o $(COMMON_ROUTE)semaforo.c $(COMMON_ROUTE)semaforo.h
	$(CC) $(FG) -c $(COMMON_ROUTE)semaforo.c $(HEADERS_COMMON)

mensaje.o: clave_recurso.o $(COMMON_ROUTE)mensaje.c $(COMMON_ROUTE)mensaje.h
	$(CC) $(FG) -c $(COMMON_ROUTE)mensaje.c $(HEADERS_COMMON)

memcomp.o: clave_recurso.o $(COMMON_ROUTE)memcomp.c $(COMMON_ROUTE)memcomp.h
	$(CC) $(FG) -c $(COMMON_ROUTE)memcomp.c $(HEADERS_COMMON)

clave_recurso.o: $(COMMON_ROUTE)clave_recurso.c $(COMMON_ROUTE)clave_recurso.h
	$(CC) $(FG) -c $(COMMON_ROUTE)clave_recurso.c $(HEADERS_COMMON)

.PHONY: clean
clean:
	rm -rf *.o