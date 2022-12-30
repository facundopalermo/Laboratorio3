#include "autos.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "./common/mensaje.h"
#include "./common/global.h"
#include <time.h>

int main(int argc, char const *argv[])
{
    int id_cola_mensajes; 
    pthread_t *idHilo; 
    int alguien_gano=0;

    srand(time(NULL));


    id_cola_mensajes=creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes); 
    
    printf("Ingresa cualqueir tecla\n");
    getchar(); 

    idHilo = (pthread_t*)malloc(sizeof(pthread_t)*CANT_AUTOS);


    if(jugar(idHilo, id_cola_mensajes, &alguien_gano)==-1){

        printf("ERROR\n");
        return -1; 

    }

    free(idHilo); 


    return 0;
}
