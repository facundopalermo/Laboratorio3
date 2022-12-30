# Crea los programas
# ./rev
# ./jug

CC = gcc
FG = -Wall -O1 -std=gnu89 -pedantic-errors -Werror
FGT = $(FG) -pthread

HEADERS_ROUTE = ./headers/
F_HEADERS_ROUTE = -I$(HEADERS_ROUTE)

COMMON_ROUTE = ./common/
RUTA_R = ./revolver/
RUTA_J = ./jugadores/

.PHONY: all
all: revolver jugadores

revolver: $(RUTA_R)revolver.c $(HEADERS_ROUTE)revolver.h revolver_f.o global.o mensaje.o threads.o clave_recurso.o
	$(CC) $(FGT) -o rev $(RUTA_R)revolver.c revolver_f.o global.o mensaje.o threads.o clave_recurso.o $(F_HEADERS_ROUTE)

jugadores: $(RUTA_J)jugadores.c $(HEADERS_ROUTE)jugadores.h jugadores_f.o global.o mensaje.o threads.o clave_recurso.o
	$(CC) $(FGT) -o jug $(RUTA_J)jugadores.c jugadores_f.o global.o mensaje.o threads.o clave_recurso.o $(F_HEADERS_ROUTE)

revolver_f.o: $(RUTA_R)revolver_f.c $(HEADERS_ROUTE)revolver_f.h global.o mensaje.o threads.o clave_recurso.o
	$(CC) $(FG) -c $(RUTA_R)revolver_f.c $(F_HEADERS_ROUTE)

jugadores_f.o: $(RUTA_J)jugadores_f.c $(HEADERS_ROUTE)jugadores_f.h global.o mensaje.o threads.o clave_recurso.o
	$(CC) $(FG) -c $(RUTA_J)jugadores_f.c $(F_HEADERS_ROUTE)

global.o: $(COMMON_ROUTE)global.c $(HEADERS_ROUTE)global.h mensaje.o threads.o clave_recurso.o
	$(CC) $(FG) -c $(COMMON_ROUTE)global.c $(F_HEADERS_ROUTE)

threads.o: $(COMMON_ROUTE)threads.c $(HEADERS_ROUTE)threads.h
	$(CC) $(FG) -c $(COMMON_ROUTE)threads.c $(F_HEADERS_ROUTE)

mensaje.o: clave_recurso.o $(COMMON_ROUTE)mensaje.c $(HEADERS_ROUTE)mensaje.h
	$(CC) $(FG) -c $(COMMON_ROUTE)mensaje.c $(F_HEADERS_ROUTE)

clave_recurso.o: $(COMMON_ROUTE)clave_recurso.c $(HEADERS_ROUTE)clave_recurso.h
	$(CC) $(FG) -c $(COMMON_ROUTE)clave_recurso.c $(F_HEADERS_ROUTE)

.PHONY: clean
clean:
	rm -rf *.o