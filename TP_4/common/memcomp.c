#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include "memcomp.h"
#include "memcomp.h"
#include "clave_recurso.h"

/**
 * @brief Crear Memoria
 * 
 * @param id_memoria 
 * @param size sizeof(tipo_dato)*cantidad
 * @param archivo_base 
 * @param r_clave 
 * @return void* castear al tipo de dato
 */
void* crear_memoria (int *r_id_memoria, int size, char *archivo_base, int r_clave) {
    void * puntero_memoria = NULL;
    key_t clave = crear_clave(archivo_base, r_clave);
    int id_memoria = shmget(clave, size, 0777|IPC_CREAT);
    if ( id_memoria == -1 ) {
        printf("No se ha podido obtener id para memoria compartida\n");
        exit(EXIT_FAILURE);
    }
    puntero_memoria = (void*) shmat(id_memoria, (char *) 0, 0);
    if ( puntero_memoria == NULL) {
        printf("No se ha podido obtener puntero a memoria compartida.\n");
    }

    *r_id_memoria = id_memoria;
    return puntero_memoria;
}

void liberar_memoria (void * memoria, int id_memoria) {
    shmdt( (char*) memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *) NULL);
}