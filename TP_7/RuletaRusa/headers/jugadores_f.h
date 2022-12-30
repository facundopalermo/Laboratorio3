#ifndef __JUGADORES_F_H
#define __JUGADORES_F_H

    #include "global.h"

    typedef struct dato {
        int id;
        int *vector_tambor;
        int id_cola_msg;
        int *disparo;
        char mensaje[LARGO_CADENA];
    }Dato;

    void *hiloJugador(void *parametros);
    int jugar(pthread_t *jugador, int *vector_tambor, int id_cola_msg);

#endif

