/* SIMULACION DE PEAJE - PEAJE */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "autos.h" // contiene la definiciones y constantes
#include "../common/funciones_varias.h" //contiene funcion de aleatorio
#include "../common/global.h" //contiene constantes para semaforos y memoria compartida
#include "../common/semaforo.h" //para todas las funciones sobre semaforos
#include "../common/memcomp.h" //para todas las funciones sobre memoria compartida

int main(int argc, char const *argv[]){
    
    int *vehiculos_en_cola = NULL;

    int id_semaforo = 0;
    int id_memoria = 0;
    int cant_de_vias = 0;
    int sig_via = 0;

    //verifica parametros
    if ( argc == 2 ){
        cant_de_vias = atoi(argv[1]);
    } else {
        printf("Debe indicar unicamente un parametro entero\n");
        exit(EXIT_FAILURE);
    }

    vehiculos_en_cola = (int*)crear_memoria(&id_memoria, sizeof(int)*cant_de_vias, ARCHIVO_BASE, CLAVE_BASE);
    
    id_semaforo = crear_semaforo(ARCHIVO_BASE, CLAVE_BASE);

    while (1) {

        espera_semaforo(id_semaforo);
        //seccion critica

            sig_via = seleccionar_via(vehiculos_en_cola, cant_de_vias);
            // la funcion seleccionar_via recorre la memoria y busca la sig_via con la menor cantidad de autos. 

            printf("Auto ingresando por via %d.\n", sig_via+1);
            vehiculos_en_cola[sig_via]++; //incrementa en 1 los autos en cola

        //fin seccion critica
        levanta_semaforo(id_semaforo);
        usleep((aleatorio(MIN_ESPERA, MAX_ESPERA))*1000);
    }

}