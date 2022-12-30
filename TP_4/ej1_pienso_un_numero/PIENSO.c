/* PIENSO UN NUMERO - PIENSO */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "datos.h" // contiene la estructura de datos y constantes
#include "../common/funciones_varias.h" //contiene funcion de aleatorio
#include "../common/global.h" //contiene constantes para semaforos y memoria compartida
#include "../common/semaforo.h" //para todas las funciones sobre semaforos
#include "../common/memcomp.h" //para todas las funciones sobre memoria compartida


int main(int argc, char const *argv[]) {
    
    int local_pienso_un_numero = 0;

    int id_memoria = -1;
    int id_semaforo = -1;
    int estado_acierto = 0; // para condicion del while
    
    Juego *memoria = NULL;
    //puntero a tipo de dato para la memoria compartida. Juego está definido en ./datos.h

    srand(time(NULL)); //para que el random de aleatorio() retorne diferentes aleatorios
    
    memoria = (Juego*) crear_memoria(&id_memoria, sizeof(Juego), ARCHIVO_BASE, CLAVE_BASE);

    //inicializo memoria.
    memoria->estado_acierto=0;
    memoria->numero_pensado=0;

    id_semaforo = crear_semaforo(ARCHIVO_BASE, CLAVE_BASE);
    iniciar_semaforo(id_semaforo, VERDE);

    local_pienso_un_numero = aleatorio (1, 99); //primer paso del juego

    printf("Esperando que el jugador conecte y adivine...\n");

    while ( estado_acierto == 0 ) {

        espera_semaforo(id_semaforo);
        //seccion critica

            if ( memoria->numero_pensado == local_pienso_un_numero ) {
                memoria->estado_acierto = 1;
                estado_acierto = 1;
                printf("Ganador: %s\n", memoria->nombre_jugador);
            } else {
                memoria->numero_pensado = 0;
                memoria->estado_acierto = 0;
            }
        
        //fin seccion critica
        levanta_semaforo(id_semaforo);
    }

    //libero memoria al finalizar
    liberar_memoria(memoria, id_memoria);
    printf("Gracias por jugar.\n");

    return 0;
}