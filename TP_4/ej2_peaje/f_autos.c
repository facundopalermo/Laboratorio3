#include "autos.h"

//funcion que retorna la via con menos autos
int seleccionar_via (int array[], int cant) {

    int menor = array[0];
    int via = 0;

    for (int i = 0; i < cant ; i++){
        if ( array[i] < menor ){
            menor = array[i];
            via = i;
        }
    }
    return via;
}