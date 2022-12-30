#ifndef __PIZZERO_F_H
#define __PIZZERO_F_H

    #include "./common/global.h"

    typedef struct datos {
        int id;
        int id_cola_mensaje;
        int id_semaforo;
        Pizzeria *pizzas_hechas;
        int *horno;
    }Datos;

    void *pizzeroThread(void* parametros);
    int cocinar (Pizzeria *pizzas_hechas, int id_cola_mensaje, int id_semaforo);

#endif