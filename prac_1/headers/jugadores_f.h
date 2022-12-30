#ifndef __JUGADORES_H_
#define __JUGADORES_H_


    #include <pthread.h>

    #define INTERVALO 300

    typedef struct jugadores
    {
        int id_cola_mensajes; 
        int nro; 
        int *ganador;
        int puntos;  
        int id_semaforo; 



    }Jugadores;
    
    int jugar(pthread_t *idHilo, int id_cola_mensajes, int cant_jugadores, int id_semaforo);
    void *hiloJugador(void *parametros); 



#endif