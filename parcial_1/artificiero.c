#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../common/semaforo.h"
#include "../common/memcomp.h"
#include "../common/global.h"
#include "../common/funciones.h"
#include "artificiero.h"

int main(int argc, char const *argv[]) {

    int cant_cables = 0;
    int cant_artificieros = 0;
    int id_artificiero = 0;

    int *cables_seleccionados = NULL; //para guardar un orden aleatorio de cortar los cables

    int cable = 0; //para usar de indice al seleccionar un cable
    int intentos = 0;
    int evaluar = 1; //al igual que en bomba, es para evaluar si seguir jugando.

    int id_semaforo = -1;
    int id_memoria = -1;

    Bomba *bombas = NULL;

    srand(time(NULL)); //inicia semilla para aleatorios diferentes
    
    if (argc == 4) {
        //evaluo los parametros
        cant_cables = atoi(argv[1]);
        cant_artificieros = atoi(argv[2]);
        id_artificiero = atoi(argv[3])-1; // -1 es porque los indices inician en 0, pero los artificieros en 1

    } else {
        printf("Debe inciar el programa con 3 parametros:\n");
        printf("./arti cant_cables cant_artificieros id_artificieros\n");
        exit(EXIT_FAILURE);
    }

    if(id_artificiero < 0 && id_artificiero >= cant_artificieros){
        printf("El identificador del artificiero debe ser mayor a 0 y menor o igual a la cantidad de artificieros.\n");
        exit(EXIT_FAILURE);
    }

    cables_seleccionados = (int*)malloc(sizeof(int)*cant_cables); //array de tamaño cant_cables y de tipo int para guardar los n cables de forma aleatoria
    /*si bien el enunciado dice que se generan los aleatorios luego del semaforo, 
    me pareció mejor generar los num//y dejo de evaluar//y dejo de evaluareros afuera y asi no bloquear el recurso mas tiempo por cada jugador.*/

    //asigno el puntero bomba al espacio obtenido con la funcion crear_memoria
    bombas = (Bomba*)crear_memoria(&id_memoria, sizeof(Bomba)*cant_cables, ARCHIVO_BASE, CLAVE_BASE);

    //creo semaforo (solo un proceso lo inicia)
    id_semaforo = crear_semaforo (ARCHIVO_BASE, CLAVE_BASE);

    //genero un array de cant_cables con los cables de forma aleatiora. se recorrera de a uno por vez 
    rndSinrepetir(1, cant_cables, cables_seleccionados);

    while (evaluar == 1) {

        espera_semaforo(id_semaforo);
        //seccion critica

            // si el estado es listo para cortar (2)
            if(bombas[id_artificiero].estado_bomba == 2){
                //corto el cable
                intentos++; //suma un intento
                bombas[id_artificiero].estado_bomba = 0; //coloca en 0 para que el proceso bomba evalue
                bombas[id_artificiero].cableSeleccionado = cables_seleccionados[cable]; //digo que cable quiero (cable es el indice del array)
                printf("En el intento %d se selecciona el cable %d\n", intentos, cables_seleccionados[cable]);
                cable++;//sumo uno al indice que indica el proximo cable a evaluar.
            }

            //luego, evalua si alguien ya corto el cable (adivinó o explotó)
            //recorro todo el vector en memoria compartida
            for(int i = 0; i < cant_artificieros; i++){
                if(bombas[i].estado_bomba == 1){
                    //si ya fue desactiva, muestro los datos obtenidos de la memoria compartida
                    printf("La bomba ya fue desactivada por el artificiero %d.\n", bombas[i].numero_artificiero);
                    evaluar = 0; //y dejo de evaluar
                }else if (bombas[i].estado_bomba==3){
                    //si ya explotó, muestro a quien le explotó
                    printf("La bomba le explotó al artificiero %d.\n", bombas[i].numero_artificiero);
                    evaluar = 0; //y dejo de evaluar
                }
            }
        //fin seccion critica
        levanta_semaforo(id_semaforo);
        usleep(aleatorio(ESPERA_MIN, ESPERA_MAX)*1000); //Espera entre 200 y 800ms
    }

    free(cables_seleccionados); //libero la memoria dinamica creada para el array de cables aleatorios
    printf("Gracias por jugar\n");
    return 0;
}