#!/bin/bash

#EJERCICIO 1
gcc ./ej1_pienso_un_numero/PIENSO.c ./common/clave_recurso.c ./common/funciones_varias.c ./common/memcomp.c ./common/semaforo.c -I./common/ -o pienso;
gcc ./ej1_pienso_un_numero/JUGADOR.c ./common/clave_recurso.c ./common/funciones_varias.c ./common/memcomp.c ./common/semaforo.c -I./common/ -o jugador;

#EJERCICIO 2
gcc ./ej2_peaje/PEAJE.c ./ej2_peaje/f_peaje.c ./common/clave_recurso.c ./common/funciones_varias.c ./common/memcomp.c ./common/semaforo.c -I./common/ -o peaje;
gcc ./ej2_peaje/AUTOS.c ./ej2_peaje/f_autos.c ./common/clave_recurso.c ./common/funciones_varias.c ./common/memcomp.c ./common/semaforo.c -I./common/ -o autos;

#EJERCICIO 3
gcc ./ej3_colchonera/COLCHONERIA.c ./ej3_colchonera/f_colchoneria.c ./common/clave_recurso.c ./common/memcomp.c ./common/semaforo.c -I./common/ -o colchon;
gcc ./ej3_colchonera/VENDEDOR.c ./ej3_colchonera/f_vendedor.c ./common/clave_recurso.c ./common/memcomp.c ./common/semaforo.c -I./common/ -o vendedor;