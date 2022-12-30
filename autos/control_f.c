#include "control_f.h"


#include "./common/global.h"
#include "./common/mensaje.h"
#include "./common/sharem.h"
#include "./common/hilos.h"


#include <pthread.h>
#include <unistd.h>

void *hiloControl(void *parametros){

    Control *datos;
    int i=0;
    char men[LARGO]={'\0'}; 
    int semaforo=0, id_cola_mensajes; 

    datos=(Control*)parametros; 
    
    id_cola_mensajes=datos->id_cola_mensajes;


    while(*datos->ganador ==0){
        
        for(i=0;i<CANT_AUTOS;i++){
            
            if(*datos->ganador==0){
                semaforo=aleatorio(ROJO, AMARILLO);
                sprintf(men, "%d", semaforo); 
                enviar_mensaje(id_cola_mensajes, MSG_AUTOS+i, MSG_CONTROL, EVT_SEMAFORO, men);
            }else{
                break; 
            }

            usleep(500*100); 

           
        }
        

    }
    pthread_exit((void*)"LISTO"); 
}


int jugar(int id_cola_mensajes){

    int i=0;
   
    mensaje msg; 
    int *estacionamiento; 
    int id_memoria; 
    pthread_t *idHilo; 
    int ganador=0; 
    Control control; 
    
    idHilo = (pthread_t*)malloc(sizeof(pthread_t)); 
    estacionamiento = (int*)creo_memoria(sizeof(int)*CANT_AUTOS, &id_memoria, CLAVE_BASE); 
    
    for(i=0;i<CANT_AUTOS; i++){
        estacionamiento[i]=0;/*inicalizo estacionamiento*/
    }

    for(i=0;i<CANT_AUTOS; i++){
       
        enviar_mensaje(id_cola_mensajes, MSG_AUTOS+i, MSG_CONTROL, EVT_ARRANCAR, "ARRANCAR");
        printf("AUTOS %d\n", i); 
    }

    control.id_cola_mensajes=id_cola_mensajes;
    control.ganador=&ganador; 
    control.estacionamiento = estacionamiento;

    if(crearThread(idHilo, hiloControl, &control)==-1){

        printf("Error al crear hilo\n");
        return -1;

    } 
    
    recibir_mensaje(id_cola_mensajes, MSG_CONTROL, &msg);
    if(msg.int_evento==EVT_GANADOR){
        pthread_mutex_lock(&mutex); 
            ganador=1; 
        pthread_mutex_unlock(&mutex); 
    }
    
    i=0; 
    /*while(i<CANT_AUTOS){
        if(estacionamiento[i]!=0){
            printf("En el puesto %d esta el auto %d\n", i+1, estacionamiento[i]);
            i+=1; 
        }
    }*/

    while(i<CANT_AUTOS){
        if(estacionamiento[i]!=0){
            printf("En el puesto %d esta el auto %d\n", i+1, estacionamiento[i]);
            i+=1; 

        }
        if(i==CANT_AUTOS){
            recibir_mensaje(id_cola_mensajes, MSG_CONTROL, &msg);
            if(msg.int_evento==EVT_GANADOR){
                pthread_mutex_lock(&mutex); 

                    ganador=1; 

                pthread_mutex_unlock(&mutex); 
            }
        }

    }
   
    printf("El ganador es %d\n", estacionamiento[0]);


    liberar_memoria(estacionamiento, id_memoria);
    free(idHilo);  

    return 0;
}



