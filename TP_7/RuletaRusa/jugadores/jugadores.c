#include "../headers/jugadores.h"

int main(int argc, char const *argv[]) {
    
    int id_cola_msg;
    int vector_tambor[CANT_JUGADORES] = {0};
    pthread_t *jugador; /*memoria dinamica se dimensiona en linea 9 y se libera en linea 14*/
    
    jugador = (pthread_t *) malloc (sizeof(pthread_t)*CANT_JUGADORES);
    id_cola_msg = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);

    if(jugar(jugador, vector_tambor, id_cola_msg) == -1) { /*funcion que 'hace todo'*/
        printf("No se ha podido iniciar el juego.\n"); /*esto pasaria si hay fallo en crear los hilos*/
        return -1;
    }

    free(jugador);

    return 0;
}
