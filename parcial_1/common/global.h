#ifndef __GLOBALES_H
#define __GLOBALES_H

    #define CLAVE_BASE 33
    #define ARCHIVO_BASE "/bin/ls"

    #define VERDE 1
    #define ROJO 0

    typedef struct dato{
        int numero_artificiero;
        int cableSeleccionado;
        int estado_bomba; //0: A evaluar, 1: Desactivado, 2: Otro intento, 3: Exploto
    } Bomba;
    
#endif