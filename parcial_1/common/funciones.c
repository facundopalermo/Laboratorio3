#include <stdlib.h>
#include "global.h"

int aleatorio(int desde, int hasta){
    return rand() % (hasta - desde + 1) + desde;
}

int busca_numero(int numero, int hasta, int *cables_seleccionados){
    for (int i=0; i < hasta; i++){
        if (numero == cables_seleccionados[i]){
            return 1;
        }
    }

    return 0;
}

void rndSinrepetir(int desde, int hasta, int *cables_seleccionados){

    int numero=0;
    int cond = 1;
    for(int i=0; i < hasta; i++){
        do {
            numero = aleatorio(desde, hasta);
            cond = busca_numero(numero, hasta, cables_seleccionados);
        } while (cond);
        cables_seleccionados[i]=numero;
    }

}