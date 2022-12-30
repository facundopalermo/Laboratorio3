#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "sharem.h"
#include "./clave.h"
#include "sys/ipc.h"

void *creo_memoria(int size, int *r_id_memoria, int clave_base){

    void *pr_memoria; 
    int id_memoria; 
    id_memoria= shmget(creo_clave(clave_base), size, 0777|IPC_CREAT);
    if(id_memoria==-1){
        printf("no se consiguio id memroia\n");
        exit(-1);
    }
    pr_memoria= (void*)shmat(id_memoria, (char*)0,0);
    if(pr_memoria==NULL){
        printf("No se consgiuio memoria compartda\n");
        
    }
    *r_id_memoria=id_memoria; 
    return pr_memoria; 

}

void liberar_memoria(void *memoria, int id_memoria){
    
    shmdt((char*)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds*)NULL);

}