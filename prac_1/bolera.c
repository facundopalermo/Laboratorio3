#include <stdio.h>
#include <stdlib.h>

#include "./headers/global.h"
#include "./headers/bolera_f.h"
#include "./headers/sharem.h"
#include "./headers/mensaje.h"
#include "./headers/semaforos.h"

#include <time.h>/*por el srand*/

int main(int argc, char const *argv[])
{
    
    int id_cola_mensajes;
    int id_memoria=0; 
    int *cant_jugadores; /*memoria compartida de jugadores para que ellos tambien sepan */
     

    srand(time(((void *)0)));/*semilla tiempo*/  

    cant_jugadores = (int*)creo_memoria(sizeof(int), &id_memoria, CLAVE_BASE); 
    *cant_jugadores =aleatorio(1,3); /*de 1 a 3*/

    if((id_cola_mensajes=creo_id_cola_mensajes(CLAVE_BASE))==-1){
        printf("Error en colas\n");
        return -1;
    }
    borrar_mensajes(id_cola_mensajes); /*borramos mensajes anteriores*/

    printf("Ingrese cualquier tecla para continuar...\n");
    if(scanf("abrir")==-1){
        printf("Error en scanf"); 
        return -1;
    }

    jugar(id_cola_mensajes, (*cant_jugadores)); /*funcion de bolera_f*/


    liberar_cola(id_cola_mensajes); /*libero cola solo aca*/
    liberar_memoria(cant_jugadores, id_memoria); /*solo aca libero memoria*/

    return 0;
}
