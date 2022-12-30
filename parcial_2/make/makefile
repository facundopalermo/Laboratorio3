# Crea los programas
# ejecutables:
#	hipodromo
#	caballos

CC = gcc #no pongo version porque corre nativo GCC 4.1 en Ubuntu 7.10
FG = -Wall -O1 -std=gnu89 -pedantic-errors -Werror
FGT = $(FG) -pthread

HEADERS_ROUTE = ../headers/
FG_HEADERS = -I$(HEADERS_ROUTE)

.PHONY: all
all: hipodromo caballos clean


#	PROGRAMAS
hipodromo: ../hipodromo.c hipodromo_f.o global.o mensaje.o clave_recurso.o
	$(CC) $(FG) -o hipodromo ../hipodromo.c hipodromo_f.o global.o mensaje.o clave_recurso.o $(FG_HEADERS)

caballos: ../caballos.c caballos_f.o global.o mensaje.o threads.o clave_recurso.o
	$(CC) $(FGT) -o caballos ../caballos.c caballos_f.o global.o mensaje.o threads.o clave_recurso.o $(FG_HEADERS)


#	PROCESOS PRINCIPALES *.o
hipodromo_f.o: ../hipodromo_f.c $(HEADERS_ROUTE)hipodromo_f.h global.o mensaje.o
	$(CC) $(FG) -c ../hipodromo_f.c $(FG_HEADERS)

caballos_f.o: ../caballos_f.c $(HEADERS_ROUTE)caballos_f.h global.o mensaje.o threads.o
	$(CC) $(FG) -c ../caballos_f.c $(FG_HEADERS)


#	COMUNES *.o
global.o: ../global.c $(HEADERS_ROUTE)global.h
	$(CC) $(FG) -c ../global.c $(FG_HEADERS)

threads.o: ../threads.c $(HEADERS_ROUTE)threads.h
	$(CC) $(FG) -c ../threads.c $(FG_HEADERS)

mensaje.o: clave_recurso.o ../mensaje.c $(HEADERS_ROUTE)mensaje.h
	$(CC) $(FG) -c ../mensaje.c $(FG_HEADERS)

clave_recurso.o: ../clave_recurso.c $(HEADERS_ROUTE)clave_recurso.h
	$(CC) $(FG) -c ../clave_recurso.c $(FG_HEADERS)


.PHONY: clean
clean:
	rm -rf *.o
