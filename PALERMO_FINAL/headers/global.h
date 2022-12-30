#ifndef __GLOBAL_BOLERA_H
#define __GLOBAL_BOLERA_H

    #include <sys/types.h>
    
    #define CLAVE_BASE 33
    #define ARCHIVO_BASE "/bin/ls"
    
    #define VERDE 1
    #define ROJO 0

    typedef enum {
        MSG_NADIE,
        MSG_BOLERA,
        MSG_JUGADOR
    } Destinos;

    typedef enum {
        EVT_NINGUNO,
        EVT_INICIO,
        EVT_TIRO,
        EVT_RESULTADO,
        EVT_FIN
    } Eventos;

    extern pthread_mutex_t mutex; /* definida en global.c */

    int numeroAleatorio (int desde, int hasta);

#endif
