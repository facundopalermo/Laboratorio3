#ifndef __GLOBAL_RULETARUSA_H
#define __GLOBAL_RULETARUSA_H

    #include <unistd.h>
    #include "mensaje.h"
    #include "threads.h"
    #include "memcomp.h"
    
    #define CLAVE_BASE 33
    #define ARCHIVO_BASE "/bin/ls"
    #define N_MIN 1
    #define N_MAX 99

    typedef enum {
        MSG_NADIE,
        MSG_BINGO,
        MSG_JUGADOR
    } Who;

    typedef enum {
        EVT_NINGUNO,
        EVT_BOLILLA,
        EVT_CARTON_LLENO
    } Evento;

    extern pthread_mutex_t mutex; /* definida en global.c */

    int validarJugadores( int argc, char const *argv[]);
    int numeroAleatorio (int desde, int hasta);
    int buscaNumero(int numero, int hasta, int *array);
    int numeroSinRepetir(int desde, int hasta, int *array);

#endif
