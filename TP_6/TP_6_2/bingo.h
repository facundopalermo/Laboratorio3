#ifndef __BINGO_H
#define __BINGO_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <unistd.h>
    #include <time.h>
    #include <string.h>

    #define CANTIDAD_DE_BOLILLAS 99
    #define N_CARTON 5
    #define N_MIN 1
    #define N_MAX 99
    #define TIEMPO 500
    #define T_MIN 500
    #define T_MAX 5000

    typedef struct datos {
        int jugador;
        int * bolillas;
    }Datos;

    pthread_mutex_t mutex;
    int g_carton_lleno; /*global porque lo indica el enunciado*/

    int validarJugadores( int argc, char const *argv[]);
    int numeroAleatorio (int desde, int hasta);
    int buscaNumero(int numero, int hasta, int *array);
    int numeroSinRepetir(int desde, int hasta, int *array);
    void escogerCarton(int carton[]);
    void mostrarCarton(int carton[], int jugador);
    int mirarCarton(int bolilla, int carton[]);
    void * ThreadJugadores(void * parametros);
    void crearHilo (pthread_t * hilo, void *(* funcion)(void *), void * datos);
    void jugar(pthread_t *jugadores, int cant_jugadores, int *bolillas);
    void girarBombo(int *bolillas);
    char * esperarThread (pthread_t hilo);
    void esperarandoJugadores (pthread_t *jugadores, int cant_jugadores);

#endif