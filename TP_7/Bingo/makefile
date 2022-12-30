# Crea los programas
# ./bin +parametro
# ./jug +parametro

CC = gcc-4.1
FG = -Wall -O1 -std=gnu89 -pedantic-errors -Werror
FGT = $(FG) -pthread

HEADERS_ROUTE = ./headers/
F_HEADERS_ROUTE = -I$(HEADERS_ROUTE)

COMMON_ROUTE = ./common/
RUTA_B = ./bingo/
RUTA_J = ./jugadores/

.PHONY: all
all: bingo jugadores

bingo: $(RUTA_B)bingo.c $(HEADERS_ROUTE)bingo.h bingo_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FGT) -o bin $(RUTA_B)bingo.c bingo_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o $(F_HEADERS_ROUTE)

jugadores: $(RUTA_J)jugadores.c $(HEADERS_ROUTE)jugadores.h jugadores_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FGT) -o jug $(RUTA_J)jugadores.c jugadores_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o $(F_HEADERS_ROUTE)

bingo_f.o: $(RUTA_B)bingo_f.c $(HEADERS_ROUTE)bingo_f.h global.o mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FG) -c $(RUTA_B)bingo_f.c $(F_HEADERS_ROUTE)

jugadores_f.o: $(RUTA_J)jugadores_f.c $(HEADERS_ROUTE)jugadores_f.h global.o mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FG) -c $(RUTA_J)jugadores_f.c $(F_HEADERS_ROUTE)

global.o: $(COMMON_ROUTE)global.c $(HEADERS_ROUTE)global.h mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FG) -c $(COMMON_ROUTE)global.c $(F_HEADERS_ROUTE)

threads.o: $(COMMON_ROUTE)threads.c $(HEADERS_ROUTE)threads.h
	$(CC) $(FG) -c $(COMMON_ROUTE)threads.c $(F_HEADERS_ROUTE)

mensaje.o: clave_recurso.o $(COMMON_ROUTE)mensaje.c $(HEADERS_ROUTE)mensaje.h
	$(CC) $(FG) -c $(COMMON_ROUTE)mensaje.c $(F_HEADERS_ROUTE)

memcomp.o: clave_recurso.o $(COMMON_ROUTE)memcomp.c $(HEADERS_ROUTE)memcomp.h
	$(CC) $(FG) -c $(COMMON_ROUTE)memcomp.c $(F_HEADERS_ROUTE)

clave_recurso.o: $(COMMON_ROUTE)clave_recurso.c $(HEADERS_ROUTE)clave_recurso.h
	$(CC) $(FG) -c $(COMMON_ROUTE)clave_recurso.c $(F_HEADERS_ROUTE)

.PHONY: clean
clean:
	rm -rf *.o