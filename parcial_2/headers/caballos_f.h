#ifndef __CABALLOS_F_H
#define __CABALLOS_F_H

    #define METROS_MIN 10
    #define METROS_MAX 50

    #define ESPERA_MIN 100
    #define ESPERA_MAX 200

    typedef struct datos
    {
        int id;
        int id_cola_mensaje;
        int ganador;
    }Datos;
    
    void * caballoThread (void * parametros);
    int jugar(pthread_t *caballo, int cant_caballos, int id_cola_mensajes);

#endif
