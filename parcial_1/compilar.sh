#!/bin/bash

#bomba
gcc bomba.c f_bomba.c ./common/clave_recurso.c ./common/funciones.c ./common/memcomp.c ./common/semaforo.c -I./common/ -o bomba -Wall -O1

#artificiero
gcc artificiero.c ./common/clave_recurso.c ./common/funciones.c ./common/memcomp.c ./common/semaforo.c -I./common/ -o arti -Wall -O1

#sed -i -e 's/^M$//'
#sed -i -e 's/\r$//'