#ifndef __PROGRAMADOR_F_H
#define __PROGRAMADOR_F_H

    #include "./common/global.h"

    typedef struct datos {
        int id;
        int id_cola_mensajes;
        Trabajo *memcomp;
    }Datos;

    int validarParametros (int argc, char const *argv[]);
    void *programadorThread (void * parametros);
    int codear(pthread_t *hilo, int id_cola_mensaje, Trabajo *programador, int programadores);
    void manejador(int signum);

#endif