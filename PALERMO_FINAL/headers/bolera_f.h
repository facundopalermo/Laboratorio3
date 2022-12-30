#ifndef __BOLERA_F_H
#define __BOLERA_F_H

    #define CANT_MIN_JUGADORES 1
    #define CANT_MAX_JUGADORES 3

    typedef struct linea {
        int pinos;
        int intentos;
        int jugador;
        int puntos;
    } Linea;

    void jugar(int id_cola_mensajes, int cant_jugadores);


#endif
