CC = gcc
CFLAGS = -Wall -O1 -std=gnu89 -pedantic-errors -Werror -pthread


HEADERS_ROUTE = ../headers/
F_HEADERS_ROUTE = -I$(HEADERS_ROUTE)

.PHONY: all
all: bolera jugadores

bolera: ../bolera.c bolera_f.o global.o mensaje.o clave.o semaforos.o sharem.o
	$(CC) $(F_HEADERS_ROUTE) -o bolera ../bolera.c bolera_f.o global.o mensaje.o clave.o semaforos.o sharem.o $(CFLAGS)

jugadores: ../jugadores.c jugadores_f.o global.o mensaje.o clave.o semaforos.o hilos.o sharem.o
	$(CC) $(F_HEADERS_ROUTE) -o jugadores ../jugadores.c jugadores_f.o global.o mensaje.o clave.o semaforos.o hilos.o sharem.o $(CFLAGS)

bolera_f.o: ../bolera_f.c $(HEADERS_ROUTE)bolera_f.h global.o mensaje.o
	$(CC) $(F_HEADERS_ROUTE) -c ../bolera_f.c $(CFLAGS)

jugadores_f.o:	../jugadores_f.c $(HEADERS_ROUTE)jugadores_f.h global.o mensaje.o 
	$(CC) $(F_HEADERS_ROUTE) -c ../jugadores_f.c $(CFLAGS)	

global.o: ../global.c $(HEADERS_ROUTE)global.h 
	$(CC)  $(F_HEADERS_ROUTE) -c ../global.c $(CFLAGS)
	
hilos.o: ../hilos.c  $(HEADERS_ROUTE)hilos.h 
	$(CC)  $(F_HEADERS_ROUTE) -c ../hilos.c $(CFLAGS)

mensaje.o: ../mensaje.c $(HEADERS_ROUTE)mensaje.h 
	$(CC)  $(F_HEADERS_ROUTE) -c ../mensaje.c $(CFLAGS)

clave.o: ../clave.c $(HEADERS_ROUTE)clave.h 
	$(CC) $(F_HEADERS_ROUTE) -c ../clave.c  $(CFLAGS)		

semaforos.o: ../semaforos.c $(HEADERS_ROUTE)semaforos.h 
	$(CC) $(F_HEADERS_ROUTE) -c ../semaforos.c  $(CFLAGS)	

sharem.o: ../sharem.c $(HEADERS_ROUTE)sharem.h
	$(CC) $(F_HEADERS_ROUTE) -c ../sharem.c  $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o