#ifndef __GLOBAL_RULETARUSA_H
#define __GLOBAL_RULETARUSA_H

    #include <unistd.h>
    #include "mensaje.h"
    #include "threads.h"
    
    #define CLAVE_BASE 33
    #define ARCHIVO_BASE "/bin/ls"
    
    #define CANT_JUGADORES 6

    typedef enum {
        MSG_NADIE,
        MSG_REVOLVER,
        MSG_JUGADOR
    } Who;

    typedef enum {
        EVT_NINGUNO,
        EVT_INICIO,
        EVT_DISPARO,
        EVT_SALVADO,
        EVT_FIN
    } Evento;

    extern pthread_mutex_t mutex; /* definida en global.c */

#endif
