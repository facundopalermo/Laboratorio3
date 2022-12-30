#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>

#include "clave_recurso.h"

key_t crear_clave (char *archivo, int r_clave) {

    key_t clave;
    clave = ftok(archivo, r_clave);

    if ( clave == (key_t) -1 ) {
        printf("Error al crear clave para el recurso compartido.\n");
        exit(EXIT_FAILURE);
    }

    return clave;

}