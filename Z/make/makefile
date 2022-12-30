# Crea los programas

CC = gcc
FG = -Wall -O1 -std=gnu89 -pedantic-errors -Werror
FGT = $(FG) -pthread

COMMON_ROUTE = ../common/
HEADERS_COMMON = -I$(COMMON_ROUTE)

.PHONY: all
all: manager programador clean

manager: ../manager.c manager_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FGT) -o manager ../manager.c manager_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o

manager_f.o: ../manager_f.c ../manager_f.h global.o mensaje.o memcomp.o 
	$(CC) $(FG) -c ../manager_f.c

programador: ../programador.c programador_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o
	$(CC) $(FGT) -o programador ../programador.c programador_f.o global.o mensaje.o threads.o clave_recurso.o memcomp.o

programador_f.o: ../programador_f.c ../programador_f.h global.o mensaje.o memcomp.o threads.o
	$(CC) $(FG) -c ../programador_f.c

global.o: $(COMMON_ROUTE)global.c $(COMMON_ROUTE)global.h
	$(CC) $(FG) -c $(COMMON_ROUTE)global.c $(HEADERS_COMMON)

threads.o: $(COMMON_ROUTE)threads.c $(COMMON_ROUTE)threads.h
	$(CC) $(FG) -c $(COMMON_ROUTE)threads.c $(HEADERS_COMMON)

mensaje.o: clave_recurso.o $(COMMON_ROUTE)mensaje.c $(COMMON_ROUTE)mensaje.h
	$(CC) $(FG) -c $(COMMON_ROUTE)mensaje.c $(HEADERS_COMMON)

memcomp.o: clave_recurso.o $(COMMON_ROUTE)memcomp.c $(COMMON_ROUTE)memcomp.h
	$(CC) $(FG) -c $(COMMON_ROUTE)memcomp.c $(HEADERS_COMMON)

clave_recurso.o: $(COMMON_ROUTE)clave_recurso.c $(COMMON_ROUTE)clave_recurso.h
	$(CC) $(FG) -c $(COMMON_ROUTE)clave_recurso.c $(HEADERS_COMMON)

.PHONY: clean
clean:
	rm -rf *.o