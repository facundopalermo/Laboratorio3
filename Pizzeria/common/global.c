#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "global.h"


pthread_mutex_t mutex;

int validarJugadores( int argc, char const *argv[]) {

    int jugadores = 0;

    if (argc == 2) {
        jugadores = atoi(argv[1]);
    } else if (argc < 2) {
        printf("Debe indicar la cantidad de jugadores como parametro al iniciar el juego.\n");
        return -1;
    } else if (argc > 2) {
        printf("Solo se admite un parametro para iniciar el juego: cantidad de jugadores.\n");
        return -1;
    }
    if ( jugadores < 1 ) {
        printf("La cantidad de jugadores no puede ser menor a 1\n");
        return -1;
    }

    return jugadores;
}

int numeroAleatorio (int desde, int hasta) {
    return rand() % (hasta - desde + 1) + desde;
}

/*Funcion que busca en el array para no repetir numeros*/
int buscaNumero(int numero, int hasta, int *array){
    int i;
    for (i=0; i < hasta; i++){
        if (numero == array[i]){
            return 1;
        }
    }

    return 0;
}

/*Funcion que retorna un numero aleatorio sin repetir. Se usa para generar los cartones y para el Bombo*/
int numeroSinRepetir(int desde, int hasta, int *array){

    int numero=0;
    int cond = 1;
    do {
        numero = numeroAleatorio(desde, hasta);
        cond = buscaNumero(numero, hasta, array);
    } while (cond);

    return numero;
}