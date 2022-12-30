#ifndef __THREADS_H
#define __THREADS_H

    #include <sys/types.h>

    int crear_thread (pthread_t * hilo, void *(*funcion)(void *), void * datos);
    void esperar_thread (pthread_t hilo);

#endif
