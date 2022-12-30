#include <stdio.h>
#include <stdlib.h>
#include "funciones_varias.h"

//aunqe se llame funciones_varias, tiene una sola.. se podrian agregar todas las que quiera.
//esta solo genera el aleatorio que tanto se usa en los ejercicios.
/**
 * @brief Genera un aleatorio, que para que funcione bien (genere aleatorios diferentes) hay que declarar srand(time(NULL)) al principio del programa (en el main)
 * 
 * @param desde 
 * @param hasta 
 * @return int 
 */
int aleatorio (int desde, int hasta) {
    return rand() % (hasta - desde + 1) + desde;
}