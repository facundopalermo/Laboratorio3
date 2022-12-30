#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./headers/memcomp.h"
#include "./headers/global.h"
#include "./headers/bolera_f.h"
#include "./headers/mensaje.h"


int main (int argc, char const *argv[]) {

    int *cant_jugadores;
    int id_memoria = 0;
    int id_cola_mensajes;
    
    /* semilla para el random */
    srand(time((void*)0));

    /* para que jugadores sepa la cantidad de jugadores, en la realidad depende de la cantidad de pistas */
    /* por eso decidí hacerlo en bolera */
    cant_jugadores = (int*)crear_memoria(&id_memoria, sizeof(int), ARCHIVO_BASE, CLAVE_BASE);

    (*cant_jugadores) = numeroAleatorio(CANT_MIN_JUGADORES, CANT_MAX_JUGADORES);

    id_cola_mensajes = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);

    printf("Jugadores: %d\n", *cant_jugadores);
    printf("Va a iniciar el juego\n. Presione enter para continuar, y a continuacion inicie los jugadores.");
    scanf("enter");

    jugar(id_cola_mensajes, *cant_jugadores);

    printf("Fin del juego\n");
    /* se libera la memoria compartida y la cola de mesajes */
    liberar_memoria(cant_jugadores, id_memoria);
    liberar_cola_mensajes(id_cola_mensajes);

    return 0;
}
