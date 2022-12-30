#ifndef __JUGADORES_F_H
#define __JUGADORES_F_H

    #include "global.h"

    #define N_CARTON 5

    typedef struct datos {
        int id;
        int aciertos;
        int id_cola_msg;
        int cant_jugadores;
    }Datos;

    void escogerCarton(int carton[]);
    void mostrarCarton(int carton[], int jugador);
    int mirarCarton(int bolilla, int carton[]);
    void * threadJugador (void * parametros);
    int jugar(pthread_t *jugadores, int cant_jugadores, int id_cola_msg);

#endif