#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "./headers/threads.h"

int crear_thread (pthread_t * hilo, void *(*funcion)(void *), void * datos) {

    pthread_attr_t atributos;
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    if ( pthread_create (hilo, &atributos, funcion, datos) != 0 ) { 
        printf("Error al crear el thread.\n");
        return -1;
    }

    return 1;
}

void esperar_thread (pthread_t hilo) {
    pthread_join (hilo, (void**) 0);
}
