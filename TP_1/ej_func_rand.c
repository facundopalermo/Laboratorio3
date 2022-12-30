//funcion generica generadora de numeros aleatorios
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generaAleatorios (int idesde, int ihasta, int cantidad, int vector[]);

void generaAleatorios (int idesde, int ihasta, int cantidad, int vector[]){
    srand(time(NULL));

    for (int i=0; i < cantidad; i++){
        vector[i] = rand() % (ihasta - idesde + 1) + idesde;
    }
    
}

