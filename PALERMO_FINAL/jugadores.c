#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

#include "./headers/memcomp.h"
#include "./headers/global.h"
#include "./headers/jugadores_f.h"
#include "./headers/mensaje.h"


int main (int argc, char const *argv[]) {

    int *cant_jugadores;
    int id_memoria = 0;
    int id_cola_mensajes;
    pthread_t *jugador;

    /* crea el acceso a la memoria compartida */
    cant_jugadores = (int*)crear_memoria(&id_memoria, sizeof(int), ARCHIVO_BASE, CLAVE_BASE);

    id_cola_mensajes = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);
    /*la bolera inicializa los mensajes*/

    printf("Inicie primero la bolera\n. Presione enter para continuar");
    scanf("enter");
    printf("Jugadores: %d\n", *cant_jugadores);

    jugador = (pthread_t*) malloc (sizeof(pthread_t) * (*cant_jugadores));

    if(jugar(id_cola_mensajes, *cant_jugadores, jugador) == -1) {
        free(jugador); /* en caso de error se libera la memoria de los hilos */
        return (-1);
    }
    
    /* la bolera libera memoria compartida y cola de mensajes */
    /* se libera la memoria de los hilos */
    free(jugador);
    return 0;
}
