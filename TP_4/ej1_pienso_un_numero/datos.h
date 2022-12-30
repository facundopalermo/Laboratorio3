#ifndef __DATOS_H
#define __DATOS_H

    #define LARGO_NOMBRE 100

    typedef struct juego {
        char nombre_jugador[LARGO_NOMBRE];
        int numero_pensado;
        int estado_acierto; // 0: no acierto | 1: acierto
    }Juego;

#endif