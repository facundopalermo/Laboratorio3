#ifndef __MEMCOMP_H
#define __MEMCOMP_H
    
    #include <sys/shm.h>
    #include "clave_recurso.h"

    void* crear_memoria (int *r_id_memoria, int size, char *archivo_base, int r_clave);
    void liberar_memoria (void * memoria, int id_memoria);

#endif