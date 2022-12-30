# Crea los programas
# ejecutables:
#	main1
#	main2

CC = gcc #no pongo version porque corre nativo GCC 4.1 en Ubuntu 7.10
FG = -Wall -O1 -std=gnu89 -pedantic-errors -Werror
FGT = $(FG) -pthread

HEADERS_ROUTE = ../headers/
FG_HEADERS = -I$(HEADERS_ROUTE)

#	compila los programas y limpia los archivo objeto
.PHONY: all
all: main1 main2 clean


#	MAIN DE PROGRAMAS
main1: ../main1.c main1_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o semaforo.o
	$(CC) $(FGT) -o main1 ../main1.c main1_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o semaforo.o $(FG_HEADERS)

main2: ../main2.c main2_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o semaforo.o
	$(CC) $(FGT) -o main2 ../main2.c main2_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o semaforo.o $(FG_HEADERS)


#	FUNCIONES DE PROGRAMAS *.o
main1_f.o: ../main1_f.c $(HEADERS_ROUTE)main1_f.h global.o mensaje.o memcomp.o threads.o semaforo.o
	$(CC) $(FG) -c ../main1_f.c $(FG_HEADERS)

main2_f.o: ../main2_f.c $(HEADERS_ROUTE)main2_f.h global.o mensaje.o memcomp.o threads.o semaforo.o
	$(CC) $(FG) -c ../main2_f.c $(FG_HEADERS)


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