#ifndef __JUGADORES_F_H
#define __JUGADORES_F_H

    #include <sys/types.h>

    #define ESPERA 300

    typedef struct datos
    {
        int id;
        int id_cola_mensaje;
        int puntos;
        int id_semaforo;
    }Datos;

    void * jugadorThread (void * parametros);
    int jugar(int id_cola_mensajes, int cant_jugadores, pthread_t *jugador);

#endif
