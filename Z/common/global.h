#ifndef __GLOBAL_PIZZERIA_H
#define __GLOBAL_PIZZERIA_H

    #include <sys/types.h>
    
    #define CLAVE_BASE 33
    #define ARCHIVO_BASE "/bin/ls"
    
    #define VERDE 1
    #define ROJO 0

    #define MIN_PROGRAMADORES 2

    typedef struct trabajo {
        int id_programador;
        int lineas_hechas;
    }Trabajo;

    typedef enum {
        MSG_NADIE,
        MSG_LIDER,
        MSG_PROGRAMADORES
    } Destinos;

    typedef enum {
        EVT_NADA, 
        EVT_CODEAR, 
        EVT_REVISAR, 
        EVT_FIN
    } Eventos;

    extern pthread_mutex_t mutex; /* definida en global.c */

    int numeroAleatorio (int desde, int hasta);

#endif
