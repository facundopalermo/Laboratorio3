#ifndef __SEM_H
#define __SEM_H


    #define VERDE 1
    #define ROJO 0


    int creo_semaforo(int clave_base);
    void inicializo_semaforo(int id_semaforo, int valor);
    void espero_semaforo(int id_semaforo);
    void levanto_semaforo(int id_semaforo);


#endif