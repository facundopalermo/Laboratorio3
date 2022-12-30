#include <stdio.h>
#include <stdlib.h>
#include "peaje.h"

//funcion que guarda en archivo registro.txt la cantidad de liberaciones
void guardar_liberacion (int cont_liberaciones) {
    FILE *archivo;
    
    if( (archivo = fopen ("registro.txt", "w")) == NULL ) {
        printf("Error al guardar registro...\n");
    } else {
        fprintf(archivo, "%d", cont_liberaciones);
    }

    fclose(archivo);
}

//funcion que muestra los autos por vias.
void mostrar_datos(int array[], int cant) {
    
    system("clear");
    for( int i = 0; i < cant; i++ ) {
        printf("VIA [%d]\t\t%d Vehículos.\n", i+1, array[i]);
    }

}