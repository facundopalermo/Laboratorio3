#ifndef __VENDEDOR_H
#define __VENDEDOR_H

    #include "./common/global.h"

    #define CLIENTE_CADA_DESDE 500
    #define CLIENTE_CADA_HASTA 5000

    typedef enum {
        PRECIO_MUZZARELLA = 1000,
        PRECIO_CALABRESA = 1300,
        PRECIO_PRIMAVERA = 1500,
        PRECIO_ANCHOAS = 2000,
        PRECIO_NAPOLITANA = 1200
    } Precios;

    void abrir_local(Pizzeria *pizzas_hechas, int id_cola_mensaje, int id_semaforo);
    void calcular_resultado(Pizzeria *pizzas_hechas);
    int limpiar (Pizzeria *pizzas_hechas, int id_memcomp, int id_cola_mensaje);

#endif