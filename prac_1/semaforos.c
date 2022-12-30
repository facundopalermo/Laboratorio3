#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include "semaforos.h"
#include "clave.h"


int creo_semaforo(int clave_base){

    int id_semaforo;
    id_semaforo = semget(creo_clave(clave_base), 1, 0600|IPC_CREAT);
    if(id_semaforo==-1){                          
        printf("No se consiguio sem\n");
        return -1;
    }
    return id_semaforo;

}

void inicializo_semaforo(int id_semaforo, int valor){

    semctl(id_semaforo, 0, SETVAL, valor);

}


void espero_semaforo(int id_semaforo){

    struct sembuf operacion;
    operacion.sem_num=0;
    operacion.sem_op=-1;
    operacion.sem_flg=0;
    semop(id_semaforo, &operacion, 1);

}


void levanto_semaforo(int id_semaforo){

    struct sembuf operacion;
    operacion.sem_num=0;
    operacion.sem_op=1;
    operacion.sem_flg=0;
    semop(id_semaforo, &operacion, 1);

}