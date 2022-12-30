#ifndef __PIENSO_H
#define __PIENSO_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <unistd.h>
    #include <time.h>
    #include <string.h>

    #define N_MIN 1
    #define N_MAX 99
    #define ESPERA_MIN 500
    #define ESPERA_MAX 5000

    typedef struct datos {
        int jugador;
        int numero_pensado;
        int intentos;
        int * alguien_acerto;
    } Datos;

    int validarJugadores( int argc, char const *argv[]);
    int piensoNumero (int desde, int hasta);
    int buscaNumero(int numero, int hasta, int *array);
    int piensoNumeroSinRepetir(int desde, int hasta, int *array);
    void jugar(pthread_t *jugador, int numero_pensado, int* alguien_acerto, int cant_jugadores); 
    void esperarandoJugadores (pthread_t *jugadores, int cant_jugadores, Datos *datos);


    pthread_mutex_t mutex;

#endif