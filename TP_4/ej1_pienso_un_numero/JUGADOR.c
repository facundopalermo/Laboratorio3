/* PIENSO UN NUMERO - JUGADOR */
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

    int id_memoria = -1;
    int id_semaforo = -1;
    int estado_acierto = 0; // para condicion del while
    int contador = 0; //para contar los intentos
    char mensaje[25]; //solo para crear el string que contiene la cantidad de intentos
    char nombre[LARGO_NOMBRE];

    Juego *memoria = NULL;
    //puntero a tipo de dato para la memoria compartida. Juego está definido en ./datos.h

    srand(time(NULL)); //para que el random de aleatorio() retorne diferentes aleatorios

    memoria = crear_memoria(&id_memoria, sizeof(Juego), ARCHIVO_BASE, CLAVE_BASE);
    id_semaforo = crear_semaforo(ARCHIVO_BASE, CLAVE_BASE);

    printf("Ingrese su nombre: ");
    scanf("%s", nombre);
    
    //inicializo memoria
    memoria->estado_acierto=0;
    memoria->numero_pensado=0;
    strcpy(memoria->nombre_jugador, nombre);

    while ( estado_acierto == 0 ) {

        espera_semaforo(id_semaforo);
        //seccion critica

            if ( memoria->estado_acierto == 0 && memoria->numero_pensado == 0 ) {
                memoria->numero_pensado = aleatorio(1, 99);
                contador ++;
            } else if ( memoria->estado_acierto == 1 && memoria->numero_pensado != 0 ) {
                estado_acierto = 1; // para salir del bucle (ya que no debo acceder desde el while a la memoria compartida)
            }
            
        //fin seccion critica
        levanta_semaforo(id_semaforo);

    }
    
    sprintf(mensaje, "Acertó en %d intentos!\n",contador);
    printf("%s", mensaje);
    //finalizo, PIENSO se encarga de liberar la memoria.
    return 0;
}