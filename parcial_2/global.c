#include <stdio.h>
#include <stdlib.h>

#include "./headers/global.h"

int numeroAleatorio (int desde, int hasta) {
    return rand() % (hasta - desde + 1) + desde;
}

int validar_caballos (int argc, char const *argv[]) {
    
    int cant_caballos = 0;

    if(argc == 2) {
        cant_caballos = atoi(argv[1]);
        if (cant_caballos < 2) {
            return -1;
        }
    } else {
        return -1;
    }

    return cant_caballos;
}
