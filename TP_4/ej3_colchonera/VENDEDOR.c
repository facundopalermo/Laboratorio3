/* COLCHONERA - VENDEDOR */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "datos.h" // contiene la estructura de datos y constantes
#include "vendedor.h" //define funciones de este programa
#include "../common/global.h" //contiene constantes para semaforos y memoria compartida
#include "../common/semaforo.h" //para todas las funciones sobre semaforos
#include "../common/memcomp.h" //para todas las funciones sobre memoria compartida


int main(int argc, char const *argv[]){

    int id_semaforo = -1;
    int id_memoria = -1;
    Colchones *colchones = NULL;

    colchones = (Colchones *)crear_memoria(&id_memoria, sizeof(Colchones)*CANTIDAD, ARCHIVO_BASE, CLAVE_BASE);
    id_semaforo = crear_semaforo(ARCHIVO_BASE, CLAVE_BASE);

    while (1) {
        espera_semaforo(id_semaforo);
        //seccion critica
            
            vender_colchon(colchones); //funcion que cumple la negocio

        //fin seccion critica
        levanta_semaforo(id_semaforo);
    }
    
    return 0;
}
