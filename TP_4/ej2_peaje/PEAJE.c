/* SIMULACION DE PEAJE - PEAJE */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "peaje.h" // contiene la definiciones y constantes
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
    int cont_liberaciones = 0;

    if ( argc == 2 ){
        cant_de_vias = atoi(argv[1]);
    } else {
        printf("Debe indicar unicamente un parametro entero\n");
        exit(EXIT_FAILURE);
    }

    vehiculos_en_cola = (int*)crear_memoria(&id_memoria, sizeof(int)*cant_de_vias, ARCHIVO_BASE, CLAVE_BASE);

    id_semaforo = crear_semaforo(ARCHIVO_BASE, CLAVE_BASE);
    iniciar_semaforo(id_semaforo, VERDE);

    //iniicializo vehiculos_en_cola
    for (int i = 0; i < cant_de_vias; i++ ) {
        vehiculos_en_cola[i] = 0;
    }

    /* En este ejercicio me tomo la libertad de interpretar que se desea que por cada iteración del while, sea atendida una via.
    Otra interpretacion podria ser que por cada iteración, se atienden de a una, pero con un for... 
    Ambas opciones estarían dentro de una via por vez cada N ms... pero me parece mas atractiva la primera opción. */

    while (1) {

        espera_semaforo(id_semaforo);

            if ( vehiculos_en_cola[sig_via] > 10 ) {
                vehiculos_en_cola[sig_via] = 0;
                cont_liberaciones++;
                guardar_liberacion(cont_liberaciones);
            } else if (vehiculos_en_cola[sig_via] > 0) {
                vehiculos_en_cola[sig_via]--;
            }

            if (sig_via < cant_de_vias-1){
                sig_via++;   
            } else {
                sig_via = 0;
            }

            mostrar_datos(vehiculos_en_cola, cant_de_vias);

        levanta_semaforo(id_semaforo);
        usleep((aleatorio(MIN_ESPERA, MAX_ESPERA))*1000);
    }
    
    liberar_memoria(vehiculos_en_cola, id_memoria); 
    /* Liberar_memoria nunca se ejecutaría. Igual que en los ejemplos dados, es un bucle infinito */
    return 0;
}

