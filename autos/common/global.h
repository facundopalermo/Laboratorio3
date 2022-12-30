#ifndef __GLOBAL_H
#define __GLOBAL_H

    #include <pthread.h>
    
 /*   #define TOTAL_PINOS 10
    #define DESDE 1
    #define HASTA 10*/
    #define CANT_AUTOS 5
    #define CLAVE_BASE 33
    #define LARGO 1000 /*para los array*/
    #define RECORRIDO 1000


    #define ROJO 1
    #define VERDE 2
    #define AMARILLO 3


    typedef enum{

        MSG_NADIE,
        MSG_AUTOS,
        MSG_CONTROL 

    }Destinos;

    typedef enum{

        EVT_NINGUNO,
        EVT_ARRANCAR,
        EVT_SEMAFORO,
        EVT_GANADOR,
        EVT_FIN
    }Eventos; 

    extern pthread_mutex_t mutex;/*variable global*/


    int aleatorio(int desde, int hasta);



#endif