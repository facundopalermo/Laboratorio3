#ifndef __MANAGER_F_H
#define __MANAGER_F_H

    #include <sys/types.h>
    #include "./common/global.h"

    #define MIN_LINEAS 1000

    typedef struct datos{
        int id_cola_mensaje;
        int lineas;
        int programadores;
        int *lineas_hechas;
    }Datos;
    


    int validarParametros(int argc, char const *argv[], int *lineas);
    int programar(pthread_t *lider, int programadores, int lineas, int id_cola_mensajes, Trabajo *programador);
    void *liderThread (void *parametros);

#endif