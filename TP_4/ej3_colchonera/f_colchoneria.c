#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datos.h" //contiene constantes y estructura de datos
#include "colchoneria.h" //contiene las definiciones de estas funciones

//funcion que satisface el punto 2)
void revisar_stock(Colchones *stock) {
    for( int i = 0; i < CANTIDAD; i++ ) {
        if (stock[i].cantidad < 10) {
            stock[i].cantidad++;
        }
    }
}

//funcion que satisface el punto 1) y 2)
void iniciar_stock(Colchones *stock) {

    static char *nombre_colchon[]={"PIERO", "SUAVESTAR", "CANNON", "SIMMONS", "BELMO"};

    for (int i = 0; i < CANTIDAD; i++ ){
        stock[i].codigo = i+1;
        stock[i].cantidad = 10;
        strcpy(stock[i].nombre, nombre_colchon[i]);
    }
}

//funcion extra que muestra en consola elstock actual.
void mostrar_stock(Colchones *stock) {
    system("clear");
    printf("COD  %*s  CANT\n",-LARGO_NOMBRE, "NOMBRE");
    for (int i = 0; i < CANTIDAD; i++ ){
        printf("%*d  %*s  %*d\n", 3, stock[i].codigo, -LARGO_NOMBRE, stock[i].nombre, 4,stock[i].cantidad);
    }
}