#include "pienso.h"

int main(int argc, char const *argv[]){

    int cant_jugadores = 0;
    int numero_pensado;
    int alguien_acerto = 0;

    pthread_t *jugadores; /*variable tipo pthread_t para crear los jugadores*/

    srand(time(NULL));

     /*funcion que se encarga de validar los parametros ingresados*/
    if ((cant_jugadores = validarJugadores(argc, argv)) == -1) {
        return -1;
    }

    numero_pensado = piensoNumero (N_MIN, N_MAX); /*funcion que piensa el numero a adivinar*/
    printf("El numero que pensé es el %d. No lo digas!\n\n", numero_pensado);

    jugadores = (pthread_t *) malloc (sizeof(pthread_t) * cant_jugadores);

    jugar(jugadores, numero_pensado, &alguien_acerto, cant_jugadores); /*funcion magica que hace todo*/

    printf("El ganador es el jugador %d\n", alguien_acerto + 1);

    free(jugadores); /*libero la memoria dinamica jugadores.*/
    return 0;
}

/*
    NOTA: en este ejercicio no vi necesario el uso de funciones propias por puntero
*/
