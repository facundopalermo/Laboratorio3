#include "./headers/jugadores_f.h"
#include "./headers/global.h"
#include "./headers/mensaje.h"
#include "./headers/semaforos.h"
#include "./headers/hilos.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <pthread.h>
#include <unistd.h> /*para usleerp*/



void *hiloJugador(void *parametros){

    Jugadores *jugador; 
    int id_cola_mensajes; 
    Mensaje msg; 
    int nro=0; 
    char mensaje[LARGO]={'\0'}; 
    int done=0;
    int id_semaforo;

    jugador = (Jugadores*)parametros; 
    id_cola_mensajes = jugador->id_cola_mensajes; 
    nro = jugador->nro; 
    id_semaforo=jugador->id_semaforo; 

    while(done==0 ){

        espero_semaforo(id_semaforo); 


        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro, &msg); /*recibo EVT_INICIO*/
        

        if(msg.int_evento== EVT_RESULTADO || msg.int_evento== EVT_FIN){

            printf("Soy el jugador %d y tire %d bolos\n", nro+1, atoi(msg.char_mensaje)); 
            jugador->puntos+=atoi(msg.char_mensaje); 

            if(msg.int_evento==EVT_FIN ){

                if(*jugador->ganador==0){   /*para que guarde solo el primero*/
                    *jugador->ganador=nro+1; /*termina*/
                    printf("FINNN %d\n", *jugador->ganador); 
                }


                done+=1; /*para salir del while*/
            
                
            }



        }
        /*mientras no haya recibido evt_fin*/
        if(msg.int_evento==EVT_INICIO || msg.int_evento==EVT_RESULTADO){
            printf("Soy el jugador %d y voy a tirar\n", nro+1);

            memset(mensaje, 0, LARGO); /*inicializo*/
            sprintf(mensaje, "%d", nro+1);
            enviar_mensaje(id_cola_mensajes, MSG_BOLERA, MSG_JUGADOR+nro, EVT_TIRO, mensaje);
        
            
            usleep(INTERVALO*1000); 

        }

        levanto_semaforo(id_semaforo);

    }

    pthread_exit((void*)"listo"); 



}

int jugar(pthread_t *idHilo, int id_cola_mensajes, int cant_jugadores, int id_semaforo){

    int i=0; 
    Jugadores *jugadores;
    int ganador=0; 


    jugadores = (Jugadores*)malloc(sizeof(Jugadores)*cant_jugadores); 


    for(i=0;i<cant_jugadores;i++){

        jugadores[i].nro=i; 
        jugadores[i].id_cola_mensajes=id_cola_mensajes; 
        jugadores[i].ganador = &ganador; 
        jugadores[i].puntos=0; 
        jugadores[i].id_semaforo=id_semaforo; 

        if(crearThread(&idHilo[i], hiloJugador, &jugadores[i])==-1){
            return -1; 
        }



    }

    for(i=0;i<cant_jugadores;i++){

        pthread_join(idHilo[i], (void**)NULL);
        printf("Jugador %d tuvo %d puntos\n", jugadores[i].nro+1, jugadores[i].puntos); 

    }

    printf("Ganador: jugador %d\n", ganador); 

    free(jugadores); 


    return 0; 

}