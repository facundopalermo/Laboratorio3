#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#include "./headers/clave_recurso.h"
#include "./headers/semaforo.h"

int crear_semaforo (char * archivo_base, int r_clave) {
    key_t clave;
    int id_semaforo;

    clave = crear_clave (archivo_base, r_clave);
    id_semaforo = semget (clave, 1, 0600|IPC_CREAT);
    
    if (id_semaforo == -1) {
        printf ("No se ha podido crear el semaforo\n");
        exit (EXIT_FAILURE);
    }
    return id_semaforo;
}

void iniciar_semaforo (int id_semaforo, int color) {
    semctl (id_semaforo, 0, SETVAL, color);
}

void espera_semaforo (int id_semaforo) {
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;
    semop (id_semaforo, &operacion, 1);
}

void levanta_semaforo (int id_semaforo) {
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = 1;
    operacion.sem_flg = 0;
    semop (id_semaforo, &operacion, 1);    
}