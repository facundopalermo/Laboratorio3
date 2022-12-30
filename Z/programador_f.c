#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#include "./common/global.h"
#include "./common/threads.h"
#include "./common/mensaje.h"
#include "./programador_f.h"

int bandera = 1;

int validarParametros (int argc, char const *argv[]) {

    int programadores = MIN_PROGRAMADORES;

    if(argc == 2 && atoi(argv[1]) > 2) {
        programadores = atoi(argv[1]);
    }
    return programadores;
}

void *programadorThread (void * parametros) {
    Datos *datos;
    Mensaje entrada;
    int lineas = 0;
    int i = 0;
    int trabajar = 1;

    datos = parametros;

    while (trabajar) {
        recibir_mensaje(datos->id_cola_mensajes, MSG_PROGRAMADORES + datos->id, &entrada);

        switch (entrada.evento)
        {
        case EVT_CODEAR:
            lineas = atoi(entrada.cuerpo);
            for (i = 0; i < lineas; i++) {
                usleep(10*1000);
            }
            pthread_mutex_lock(&mutex);
            (datos->memcomp->lineas_hechas)+=lineas;
            /*printf("hice %d", datos->memcomp->lineas_hechas);*/
            printf("Programador %d: codié %d lineas \n", datos->id+1, lineas);
            pthread_mutex_unlock(&mutex);
            break;

        case EVT_REVISAR:
            lineas = atoi(entrada.cuerpo);
            for (i = 0; i < lineas; i++) {
                usleep(20*1000);
            }
            printf("\tProgramador %d: revisé %d lineas \n", datos->id+1, lineas);
            break;

        case EVT_FIN:
            trabajar = 0;
            printf("Programador %d: Listo\n", datos->id+1);
            break;

        default:
            break;
        }
    }
    sleep(1);
    pthread_exit((void*) "listo");
}

int codear(pthread_t *hilo, int id_cola_mensaje, Trabajo *programador, int programadores) {

    Datos *datos;
    int i = 0;
    int pid = 0;
    char cuerpo[LARGO_CADENA];

    datos = (Datos*) malloc (sizeof(datos)*programadores);

    for (i = 0; i < programadores; i++) {

        datos[i].id = i;
        datos[i].id_cola_mensajes = id_cola_mensaje;
        datos[i].memcomp = &programador[i];

        if(crearThread(&hilo[i], programadorThread, &datos[i])== -1) {
            return -1;
        }
    }
    
    for (i = 0; i < programadores; i++) {
        pthread_join(hilo[i], (void**)0);
    }

    pid = getpid();
    sprintf(cuerpo,"%d", pid);
    enviar_mensaje(id_cola_mensaje, MSG_LIDER, MSG_PROGRAMADORES, EVT_FIN, cuerpo);

    printf("Espero señal para irnos a casa\n");
    signal(SIGUSR1, manejador);
    while(bandera){
        usleep(100*1000);
    }

    printf("Fin del dia\n");
    return 0;
}

void manejador(int signum) {
    if(signum == SIGUSR1) {
        printf("Recibímos la señal de mi finalizar %d\n", signum);
    }
    bandera = 0;
}