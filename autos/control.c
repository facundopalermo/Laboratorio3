#include "control.h"
#include <stdio.h>
#include <stdlib.h>

#include "./common/mensaje.h"
#include "./common/global.h"
#include <pthread.h>



int main(int argc, char const *argv[])
{
    
    int id_cola_mensajes; 
    

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE); 
    borrar_mensajes(id_cola_mensajes); 
    
    if(jugar(id_cola_mensajes)==-1){
        printf("Error en hilos\n");
        return -1; 
    }


    liberar_cola(id_cola_mensajes);  


    return 0;
}
