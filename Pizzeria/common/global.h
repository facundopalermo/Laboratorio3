#ifndef __GLOBAL_PIZZERIA_H
#define __GLOBAL_PIZZERIA_H

    #include <sys/types.h>
    
    #define CLAVE_BASE 33
    #define ARCHIVO_BASE "/bin/ls"
    
    #define VERDE 1
    #define ROJO 0

    #define MENU 5
    #define PIZZEROS 3
    #define PIZZAS_MAX 100

    typedef struct pizzeria {
        int pizzero;
        int pizzas[MENU];
    }Pizzeria;

    typedef enum {
        MSG_NADIE,
        MSG_VENDEDOR,
        MSG_PIZZERO
    } Who;

    typedef enum {
        EVT_NADA,
        EVT_PIZZA,
        EVT_CERRAR
    } Evento;

    typedef enum {
        MUZZARELLA,
        CALABRESA,
        PRIMAVERA,
        ANCHOAS,
        NAPOLITANA
    } Pizzas;


    extern pthread_mutex_t mutex; /* definida en global.c */

    int numeroAleatorio (int desde, int hasta);

#endif
