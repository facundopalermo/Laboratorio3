#include "./headers/clave.h"


#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>


key_t creo_clave(int clave_base){

    key_t clave;
    clave= ftok("/bin/ls", clave_base);
    if(clave==(key_t)-1){
        printf("No se pudo crear la claven\n");
        exit(-1);
    }
    return clave; 
}
