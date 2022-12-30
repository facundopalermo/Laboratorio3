#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "./common/memcomp.h"
#include "./common/mensaje.h"
#include "./common/global.h"
#include "programador_f.h"

int main(int argc, char const *argv[]) {
    
    int programadores = 0;
    int id_cola_mensaje = 0;
    int id_memoria = 0;
    Trabajo *programador;
    pthread_t *hilo;

    programadores = validarParametros (argc, argv);

    printf("presione enter para continuar...\n");
    scanf("enter");

    id_cola_mensaje = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);
    programador = (Trabajo*)crear_memoria(&id_memoria, sizeof(Trabajo)*programadores, ARCHIVO_BASE, CLAVE_BASE);
    hilo = (pthread_t*)malloc(sizeof(pthread_t)*programadores);

    pthread_mutex_init(&mutex, NULL);

    if(codear(hilo, id_cola_mensaje, programador, programadores) == -1) {
        return -1;
    }

    return 0;
}
