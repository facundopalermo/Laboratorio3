#include "autos_f.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "./common/hilos.h"
#include "./common/mensaje.h"

#include "./common/global.h"
#include "./common/sharem.h"
#include <unistd.h>



void *HiloAuto(void *parametros){

    Dato *datos; 
    int i=0; 
    int id_cola_mensajes; 
    int nro_auto=0; 
    mensaje msg; 
    int semaforo =0; 
    int done=0; 
    char mensaje[LARGO]={'\0'};
    int alguien=0; 

    datos = (Dato*)parametros; 
    id_cola_mensajes=datos->id_cola_mensajes; 
    nro_auto=datos->nro_auto-1; 
   
    printf("AUTO %d\n",nro_auto);
    while(done==0){

        
        recibir_mensaje(id_cola_mensajes, MSG_AUTOS+nro_auto, &msg); /*espera EVT_ARRANCAR*/
        pthread_mutex_lock(&mutex); 
        
        if(msg.int_evento==EVT_SEMAFORO){
            
            semaforo= atoi(msg.char_mensaje); 
           
            if(semaforo==ROJO){
                datos->recorrido+=0; 
                   
            }else if(semaforo==AMARILLO){
                datos->recorrido+=50; 
            }else{
                datos->recorrido+= aleatorio(100,200); 
            }

            if(datos->recorrido >= RECORRIDO){ /*llega a 10.000*/
                done=1;
                
                if(*datos->alguien_gano==0){
                    for(i=0;i<CANT_AUTOS;i++){
                        sprintf(mensaje, "%d", nro_auto+1); 
                        enviar_mensaje(id_cola_mensajes, MSG_AUTOS+i, MSG_AUTOS+nro_auto, EVT_GANADOR, mensaje); 

                    
                    }
                    enviar_mensaje(id_cola_mensajes, MSG_CONTROL, MSG_AUTOS+nro_auto, EVT_GANADOR, mensaje);
                }
              
                *datos->alguien_gano+=1; 
                if(*datos->alguien_gano>0){
                    alguien =*datos->alguien_gano-1; 
                    datos->estacionamiento[alguien]=datos->nro_auto; 
                }
                /*supongo*/
            }

        }else if(msg.int_evento==EVT_ARRANCAR){
            printf("AUTO ARRANCANDO %d\n", nro_auto); 

        }else if(msg.int_evento==EVT_GANADOR){
           /* done=1;*/
        }
        pthread_mutex_unlock(&mutex);

        usleep(500*100); 
        

        printf("recorrido %d de %d\n", datos->recorrido, datos->nro_auto); 
        
    }
    /*espero*/
    while(datos->estacionamiento[4]==0) {
        recibir_mensaje(id_cola_mensajes, MSG_AUTOS+nro_auto, &msg);
    }
 
    pthread_exit((void*)"LISTO"); 

}



int jugar(pthread_t *idHilo, int id_cola_mensajes, int *alguien_gano){

    Dato autos[CANT_AUTOS]; 
    int i=0, id_memoria;
    int *estacionamiento = (int*)creo_memoria(sizeof(int)*CANT_AUTOS, &id_memoria, CLAVE_BASE); 
    /*main*/

    for(i=0;i<CANT_AUTOS;i++){

        autos[i].id_cola_mensajes=id_cola_mensajes; 
        autos[i].nro_auto=i+1;
        autos[i].recorrido=0;
        autos[i].alguien_gano=alguien_gano; 
        autos[i].estacionamiento=estacionamiento; 


        if(crearThread(&idHilo[i], HiloAuto, &autos[i])==-1){

            printf("Erorr al crear hilo\n");
            return -1;
        }
    }

    for(i=0; i<CANT_AUTOS;i++){
        pthread_join(idHilo[i],(void **)0);
    }
    
    i=0; 
    while(i<CANT_AUTOS){
        if(estacionamiento[i]!=0){
            printf("En el puesto %d esta el auto %d\n", i+1, estacionamiento[i]);
            i+=1; 
        }
    }

    liberar_memoria(estacionamiento, id_memoria); 

    return 0; 

}