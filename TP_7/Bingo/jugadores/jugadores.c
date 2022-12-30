#include "../headers/jugadores.h"

int main(int argc, char const *argv[])
{
    int cant_jugadores = 0;
    int id_cola_msg;
    pthread_t *jugadores; /*se dimensiona en linea 16*/
    int id_memcomp;
    int *inicio; /*se dimensiona en linea 20 y se libera en proceso bingo*/

    if ((cant_jugadores = validarJugadores(argc, argv)) == -1) { /*verifica parametros*/
        return (-1);
    }

    id_cola_msg = crear_cola_mensaje (ARCHIVO_BASE, CLAVE_BASE);
    jugadores = (pthread_t *) malloc (sizeof(pthread_t) * cant_jugadores); /*se libera en linea 25*/

    printf("Preparen sus cartones y marcadores, el juego está por comenzar!\n\n");

    inicio = (int*) crear_memoria(&id_memcomp, sizeof(int), ARCHIVO_BASE,CLAVE_BASE); 
    *inicio = 1; /*pone en 1 la memoria compartida para que pueda iniciar el bingo*/

    jugar(jugadores, cant_jugadores, id_cola_msg);

    free(jugadores);
    return 0;
}
