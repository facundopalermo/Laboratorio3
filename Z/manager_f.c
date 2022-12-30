#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "manager_f.h"
#include "./common/global.h"
#include "./common/threads.h"
#include "./common/mensaje.h"

int validarParametros(int argc, char const *argv[], int *lineas) {

    int programadores = MIN_PROGRAMADORES;

    if(argc == 3) {
        if(atoi(argv[1]) > 1000) {
            (*lineas) = atoi(argv[1]);
        }
        if (atoi(argv[2])>2) {
            programadores = atoi(argv[2]);
        }
    }
    return programadores;
}

void * liderThread(void * parametros) {

    char cuerpo[LARGO_CADENA];
    int i = 0;
    int cant_lineas = 0;
    int revisar = 0;
    Datos *datos;
    datos = parametros; 

    while ((*datos->lineas_hechas) <= datos->lineas) {
        for (i = 0; i < datos->programadores; i++){
            
            if (revisar >= 200) {
                cant_lineas = (*datos->lineas_hechas) * 0.1;
                sprintf(cuerpo, "%d", cant_lineas);
                enviar_mensaje(datos->id_cola_mensaje, MSG_PROGRAMADORES + i, MSG_LIDER, EVT_REVISAR, cuerpo);
                printf("\t%d lineas enviadas a revisar al programador %d\n", cant_lineas, i+1);
                revisar = 0;
            } else {
                cant_lineas = numeroAleatorio(10, 50);
                sprintf(cuerpo, "%d", cant_lineas);
                enviar_mensaje(datos->id_cola_mensaje, MSG_PROGRAMADORES + i, MSG_LIDER, EVT_CODEAR, cuerpo);
                revisar += cant_lineas;
                (*datos->lineas_hechas) += cant_lineas;
                printf("%d lineas enviadas a codear al programador %d\n", cant_lineas, i+1);
                usleep(numeroAleatorio(500, 5000)*100);
            }
        }
    }

    for (i = 0; i < datos->programadores; i++) {
        enviar_mensaje(datos->id_cola_mensaje, MSG_PROGRAMADORES + i, MSG_LIDER, EVT_FIN, "nada");
        printf("mensaje enviado\n");
    }
    printf("Proyecto terminado!\n");

    pthread_exit((void*)"listo");
}

int programar(pthread_t *lider, int programadores, int lineas, int id_cola_mensajes, Trabajo *programador) {

    Datos datos;
    Mensaje entrada;
    int lineas_hechas = 0;
    int i = 0;
    int status = 0;
    pid_t pid = 0;

    datos.id_cola_mensaje = id_cola_mensajes;
    datos.lineas = lineas;
    datos.programadores = programadores;
    datos.lineas_hechas = &lineas_hechas;

    if(crearThread(lider, liderThread, &datos) == -1){
        return (-1);
    }
    
    /*pthread_join(*lider, (void**)0);*/

    printf("Espero que terminen los programdores\n");

    recibir_mensaje(id_cola_mensajes, MSG_LIDER, &entrada);
    if(entrada.evento == EVT_FIN) {
        for(i = 0; i < programadores; i++) {
            printf("Lineas hechas por programador %d: %d\n", i+1, programador[i].lineas_hechas);
        }
        pid = atoi(entrada.cuerpo);
        kill(pid, SIGUSR1);

        waitpid(pid, &status, 0);
        printf("Proceso terminado: %d\n", status);
    }

    return 0;
}