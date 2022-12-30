# makefile de banco y cajeros

CC = gcc
CFLAGS = -Wall -O1
CFLAG_COMMON = -I./common/

OBJS_BANCO = 
OBJS_COMMON = clave_recurso.o memcomp.o mensaje.o semaforo.o
OBJS_GLOBAL = ./common/global.h

.PHONY: all
all: banco cajero

banco: banco.c banco_funciones.c banco.h $(OBJS_COMMON) $(OBJS_GLOBAL)
	$(CC) $(CFLAGS) -o banco banco.c banco_funciones.c $(OBJS_COMMON) $(CFLAG_COMMON)

cajero: cajero.c cajero_funciones.c cajero.h $(OBJS_COMMON) $(OBJS_GLOBAL)
	$(CC) $(CFLAGS) -o cajero cajero.c cajero_funciones.c $(OBJS_COMMON) $(CFLAG_COMMON)

clave_recurso.o: ./common/clave_recurso.h ./common/clave_recurso.c
	$(CC) $(CFLAGS) -c ./common/clave_recurso.c $(CFLAG_COMMON)

memcomp.o: clave_recurso.o ./common/memcomp.h ./common/memcomp.c
	$(CC) $(CFLAGS) -c ./common/memcomp.c $(CFLAG_COMMON)

mensaje.o: clave_recurso.o ./common/mensaje.h ./common/mensaje.c
	$(CC) $(CFLAGS) -c ./common/mensaje.c $(CFLAG_COMMON)

semaforo.o: clave_recurso.o ./common/semaforo.h ./common/semaforo.c
	$(CC) $(CFLAGS) -c ./common/semaforo.c $(CFLAG_COMMON)

.PHONY: clean
clean:
	rm -rf *.o