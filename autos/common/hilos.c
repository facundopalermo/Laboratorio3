#include "hilos.h"

int crearThread(pthread_t *hilo, void*(*funcion)(void *), void *datos){
    pthread_attr_t atributos; 
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos,PTHREAD_CREATE_JOINABLE); 

    if(pthread_create(hilo, &atributos, funcion,datos)!=0){
        printf("Error al crear ");
        return -1;
    }
    return 1;

}