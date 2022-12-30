#include "bingo.h"

int main(int argc, char const *argv[]){
    
    int bolillas[CANTIDAD_DE_BOLILLAS] = {0};
    int cant_jugadores = 0;
    pthread_t *jugadores; /*variable tipo pthread_t para crear los jugadores*/

    g_carton_lleno = 0; /*inicializo la variable global*/

    srand(time(NULL));

    cant_jugadores = validarJugadores(argc, argv); /*valido la cantidad de jugadores*/

    printf("Preparen sus carton y marcador, y a jugar!\n");

    jugadores = (pthread_t*) malloc (sizeof(pthread_t)*cant_jugadores);

    /*funcion divertida, recibe por parametros los jugadores, su cantidad y el vector del Bombo*/
    jugar(jugadores, cant_jugadores, bolillas);
    
    printf("El ganador del bingo es el jugador %d. Felicitaciones!\n\n", g_carton_lleno + 1);

    free(jugadores);

    return 0;
}
