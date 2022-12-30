#include <stdio.h>
#include <stdlib.h>

#include "./headers/global.h"
#include "./headers/jugadores_f.h"
#include "./headers/sharem.h"
#include "./headers/mensaje.h"
#include "./headers/semaforos.h"

#include <time.h>/*por el srand*/
#include <pthread.h> /*x hilos*/

int main(int argc, char const *argv[])
{
    int id_cola_mensajes;
    int id_memoria=0; 
    int *cant_jugadores; /*memoria compartida de jugadores para que ellos tambien sepan */
    int id_semaforo=0; 

    pthread_t *idHilo; 

    srand(time(((void *)0)));/*semilla tiempo*/

    if((id_cola_mensajes=creo_id_cola_mensajes(CLAVE_BASE))==-1){
        printf("Error en colas\n");
        return -1;
    } 

    id_semaforo = creo_semaforo(CLAVE_BASE); 
    inicializo_semaforo(id_semaforo, VERDE); /*solo aca*/


    cant_jugadores = (int*)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE); 


    printf("Cant jugadores: %d \n", *cant_jugadores); 
    idHilo = (pthread_t*)malloc(sizeof(pthread_t)*(*cant_jugadores)); /*tantos hilos como jugadores*/

    if(jugar(idHilo, id_cola_mensajes, (*cant_jugadores), id_semaforo )==-1){

        printf("Error en hilos\n"); 
        free(idHilo); /*libero hilos igual */
        return -1; 

    } 

    free(idHilo); 


    return 0;
}
