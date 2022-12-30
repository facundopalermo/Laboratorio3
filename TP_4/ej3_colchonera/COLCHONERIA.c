/* COLCHONERA - COLCHONERIA */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "datos.h" // contiene la estructura de datos y constantes
#include "colchoneria.h" //define funciones de este programa
#include "../common/global.h" //contiene constantes para semaforos y memoria compartida
#include "../common/semaforo.h" //para todas las funciones sobre semaforos
#include "../common/memcomp.h" //para todas las funciones sobre memoria compartida

int main(int argc, char const *argv[]) {
    
    int id_semaforo = -1;
    int id_memoria = -1;

    Colchones *colchones = NULL; 
    //puntero a tipo de dato para la memoria compartida. Colchones está definido en ./datos.h

    colchones = crear_memoria(&id_memoria, sizeof(Colchones)*CANTIDAD, ARCHIVO_BASE, CLAVE_BASE);
    //asigna a colchones el puntero obtenido de crear_memoria. En este caso el tamaño será de 5 estructuras Colchones (CANTIDAD definido en datos.h)

    id_semaforo = crear_semaforo(ARCHIVO_BASE, CLAVE_BASE);
    iniciar_semaforo(id_semaforo, VERDE);
    //Inicio semaforo solo en este programa.

    iniciar_stock(colchones);
    /*funcion que inicializa los datos de la memoria compartida con los datos de los puntos 1) y 2)
    (en ./f_colchonera.c)*/

    while (1) {

        espera_semaforo(id_semaforo); 

        //seccion critica

            revisar_stock(colchones);//funcion que satisface el punto 4). (en ./f_colchonera.c)
            mostrar_stock(colchones);//funcion extra que muestra el stock actual

        //fin seccion critica

        levanta_semaforo(id_semaforo);

        usleep(ESPERA*1000); //espera 500ms
    }

    liberar_memoria(colchones, id_memoria);
    /* Liberar_memoria nunca se ejecutaría. Igual que en los ejemplos dados, es un bucle infinito */
    return 0;
}


