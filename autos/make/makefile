CC = gcc
CFLAGS = -Wall -O1 -std=gnu89 -pedantic-errors -pthread

COMMON_ROUTE = ../common/
F_COMMON_ROUTE = -I$(COMMON_ROUTE)

.PHONY: all
all: autos control

autos: ../autos.c ../autos.h autos_f.o global.o mensaje.o sharem.o clave.o hilos.o
	$(CC) $(F_COMMON_ROUTE) -o autos ../autos.c autos_f.o global.o mensaje.o sharem.o clave.o hilos.o $(CFLAGS)

control: ../control.c ../control.h control_f.o global.o mensaje.o clave.o sharem.o hilos.o
	$(CC) $(F_COMMON_ROUTE) -o control ../control.c control_f.o global.o mensaje.o clave.o sharem.o hilos.o $(CFLAGS)

autos_f.o: ../autos_f.c ../autos_f.h global.o mensaje.o 
	$(CC) $(F_COMMON_ROUTE) -c ../autos_f.c $(CFLAGS)

control_f.o:	../control_f.c ../control_f.h global.o hilos.o mensaje.o 
	$(CC) $(F_COMMON_ROUTE) -c ../control_f.c $(CFLAGS)	


global.o: $(COMMON_ROUTE)global.c $(COMMON_ROUTE)global.h 
	$(CC)  $(F_COMMON_ROUTE) -c $(COMMON_ROUTE)global.c $(CFLAGS)
	
hilos.o: $(COMMON_ROUTE)hilos.c  $(COMMON_ROUTE)hilos.h 
	$(CC)  $(F_COMMON_ROUTE) -c $(COMMON_ROUTE)hilos.c $(CFLAGS)

mensaje.o: $(COMMON_ROUTE)mensaje.c $(COMMON_ROUTE)mensaje.h 
	$(CC)  $(F_COMMON_ROUTE) -c $(COMMON_ROUTE)mensaje.c $(CFLAGS)

clave.o: $(COMMON_ROUTE)clave.c $(COMMON_ROUTE)clave.h 
	$(CC) $(F_COMMON_ROUTE) -c $(COMMON_ROUTE)clave.c  $(CFLAGS)		

sharem.o: $(COMMON_ROUTE)sharem.c $(COMMON_ROUTE)sharem.h 
	$(CC) $(F_COMMON_ROUTE) -c $(COMMON_ROUTE)sharem.c  $(CFLAGS)	


.PHONY: clean
clean:
	rm -rf *.o