#ifndef __AUTOS_F_
#define __AUTOS_F_


    #include <pthread.h>
    typedef struct tipo_auto{

        int id_cola_mensajes;
        int nro_auto; 
        int recorrido; 
        int *alguien_gano; 
        int *estacionamiento; 

    }Dato; 

    void *HiloAuto(void *parametros);
    int jugar(pthread_t *idHilo, int id_cola_mensajes, int *alguien_gano);



#endif