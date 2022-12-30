# Crea los programas
# ejecutables:
#	bolera
#	jugadores

CC = gcc #no pongo version porque corre nativo GCC 4.1 en Ubuntu 7.10
FG = -Wall -O1 -std=gnu89 -pedantic-errors -Werror
FGT = $(FG) -pthread

HEADERS_ROUTE = ../headers/
FG_HEADERS = -I$(HEADERS_ROUTE)

#	compila los programas y limpia los archivo objeto
.PHONY: all
all: bolera jugadores clean


#	MAIN DE PROGRAMAS
bolera: ../bolera.c bolera_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FGT) -o bolera ../bolera.c bolera_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o $(FG_HEADERS)

jugadores: ../jugadores.c jugadores_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o semaforo.o
	$(CC) $(FGT) -o jugadores ../jugadores.c jugadores_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o semaforo.o $(FG_HEADERS)


#	FUNCIONES DE PROGRAMAS *.o
bolera_f.o: ../bolera_f.c $(HEADERS_ROUTE)bolera_f.h global.o mensaje.o memcomp.o threads.o
	$(CC) $(FG) -c ../bolera_f.c $(FG_HEADERS)

jugadores_f.o: ../jugadores_f.c $(HEADERS_ROUTE)jugadores_f.h global.o mensaje.o memcomp.o threads.o semaforo.o
	$(CC) $(FG) -c ../jugadores_f.c $(FG_HEADERS)


#	COMUNES *.o
global.o: ../global.c $(HEADERS_ROUTE)global.h
	$(CC) $(FG) -c ../global.c $(FG_HEADERS)

threads.o: ../threads.c $(HEADERS_ROUTE)threads.h
	$(CC) $(FG) -c ../threads.c $(FG_HEADERS)

mensaje.o: clave_recurso.o ../mensaje.c $(HEADERS_ROUTE)mensaje.h
	$(CC) $(FG) -c ../mensaje.c $(FG_HEADERS)

memcomp.o: clave_recurso.o ../memcomp.c $(HEADERS_ROUTE)memcomp.h
	$(CC) $(FG) -c ../memcomp.c $(FG_HEADERS)

semaforo.o: clave_recurso.o ../semaforo.c $(HEADERS_ROUTE)semaforo.h
	$(CC) $(FG) -c ../semaforo.c $(FG_HEADERS)

clave_recurso.o: ../clave_recurso.c $(HEADERS_ROUTE)clave_recurso.h
	$(CC) $(FG) -c ../clave_recurso.c $(FG_HEADERS)


.PHONY: clean
clean:
	rm -rf *.o