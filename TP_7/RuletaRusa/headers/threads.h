#ifndef __THREADS_H
#define __THREADS_H

    #include <pthread.h>
    #include <stdlib.h>
    #include <stdio.h>

    int crearThread (pthread_t * hilo, void *(*funcion)(void *), void * datos);
    void esperarThread (pthread_t hilo);

#endif