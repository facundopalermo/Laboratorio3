#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "manager_f.h"
#include "./common/global.h"
#include "./common/mensaje.h"
#include "./common/memcomp.h"


int main(int argc, char const *argv[])
{
    pthread_t lider;
    int id_cola_mensajes = 0;
    int programadores = 0;
    int lineas = MIN_LINEAS;
    int id_memoria;
    Trabajo *programador;

    srand(time((void*)0));

    programadores = validarParametros(argc, argv, &lineas);

    printf("presione enter para continuar...\n");
    scanf("enter");

    id_cola_mensajes = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);

    borrar_mensajes(id_cola_mensajes);

    programador = (Trabajo*)crear_memoria(&id_memoria, sizeof(Trabajo)*programadores, ARCHIVO_BASE, CLAVE_BASE);

    if(programar(&lider, programadores, lineas, id_cola_mensajes, programador) == -1){
        return -1;
    }

    liberar_cola_mensajes(id_cola_mensajes);
    liberar_memoria(programador, id_memoria);

    return 0;
}
