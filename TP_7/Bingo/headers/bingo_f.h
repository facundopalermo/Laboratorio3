#ifndef __BINGO_F_H
#define __BINGO_F_H

    #include "global.h"

    #define T_MIN 500
    #define T_MAX 5000

    typedef struct datos {
        int cant_jugadores;
        int ganador;
        int id_cola_msg;
    }Datos;

    void * threadBolillero (void * parametros);
    int jugar(pthread_t *bolillero, int cant_jugadores, int id_cola_msg);

#endif