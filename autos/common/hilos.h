#ifndef __HILOS_H
#define __HILOS_H
    #include "pthread.h"
    #include <stdlib.h>
    #include <stdio.h>

    int crearThread(pthread_t *hilo, void*(*funcion)(void *), void *datos);



#endif