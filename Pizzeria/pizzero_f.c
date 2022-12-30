#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "./common/global.h"
#include "./common/threads.h"
#include "./common/mensaje.h"
#include "./common/semaforo.h"
#include "pizzero_f.h"


void *pizzeroThread(void* parametros) {

    Datos *datos;
    Mensaje entrada;

    int i = 0, j = 0;
    int cocinar = 1;
    int token = 0;
    int horno_libre=0;
    int comanda[MENU]={0};

    datos = (Datos*)parametros;

    while(cocinar) {

        recibir_mensaje(datos->id_cola_mensaje,MSG_PIZZERO+datos->id, &entrada);
        switch (entrada.evento) {
        case EVT_PIZZA:
            printf("Pizzero %d empieza a cocinar\n", datos->id+1);

			token = atoi(strtok(entrada.cuerpo, "|"));
            comanda[0] = token;
            datos->pizzas_hechas->pizzas[0]+=token;
            for(i=1; i < MENU; i++)
			{
                token = atoi(strtok(NULL,"|"));
				comanda[i] = token;
                (datos->pizzas_hechas[datos->id].pizzas[i])+=token;
		    }

            printf("\n");
            
            while(datos->horno[0]!=0 && datos->horno[1]!=0);
            
            pthread_mutex_lock(&mutex);
            if(datos->horno[0]==0){
                datos->horno[0] = 1;
                horno_libre = 0;
            } else {
                datos->horno[1] = 1;
                horno_libre = 1;
            }
                for(i = 0; i< MENU; i++) {
                    for(j = 0; j < comanda[i]; j++){
                        usleep(1000*100);
                    }
                }
                datos->horno[horno_libre]=0;
            pthread_mutex_unlock(&mutex);
            break;

        case EVT_CERRAR:
            cocinar = 0;
            break;
        default:
            break;
        }
    }

    pthread_exit((void*)"listo");
}

int cocinar (Pizzeria *pizzas_hechas, int id_cola_mensaje, int id_semaforo) {

    int i = 0;
    pthread_t *pizzero;
    Datos *datos;
    int horno[2]={0};

    pizzero = (pthread_t*)malloc(sizeof(pthread_t)*PIZZEROS);
    datos = (Datos*)malloc(sizeof(Datos)*PIZZEROS);

    for (i = 0; i < PIZZEROS; i++) {
        datos[i].id = i;
        datos[i].id_cola_mensaje = id_cola_mensaje;
        datos[i].id_semaforo = id_semaforo;
        datos[i].pizzas_hechas = pizzas_hechas;
        datos[i].horno = horno;

        if(crearThread(&pizzero[i], pizzeroThread, &datos[i]) == -1){
            return -1;
        }

    }
    for(i = 0; i < PIZZEROS; i++) {
       esperarThread(pizzero[i]);
    }

    enviar_mensaje(id_cola_mensaje, MSG_VENDEDOR, MSG_PIZZERO, EVT_NADA,"nada");
    printf("Al fin cerramos!\n");
    
    free(pizzero);
    free(datos);
    return 1;
}