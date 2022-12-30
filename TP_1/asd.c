#include <stdio.h>
#include <stdlib.h>
#include "ej_func_rand.c"

int main (){
    int vector[10];

    generaAleatorios(0,10,10,vector);

    for(int i=0; i<10; i++){
        printf("%d ", vector[i]);
    }
}