#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> /* libreria de control de hilos */ 
#include <unistd.h> /* para el unsleep */

#include "./headers/caballos_f.h" /* prototipos y definiciones */
#include "./headers/threads.h" /* funciones de hilos */
#include "./headers/mensaje.h"/* funciones de mensaje */
#include "./headers/global.h" /* Constantes, aleatorio, etc */


void * caballoThread (void * parametros) {

    int jugar = 0; /* bandera para el while */
    Datos *datos; /* Puntero para para acceder a los datos pasados por parametro */ 
    Mensaje entrada; /*para los mensajes recibidos*/
    int metros_recorridos = 0; /*acumulador local para los metros recorridos*/
    /*int metros_al_disco = 0; pedido en el enunciado, no se usa. Por eso lo comento */
    char cuerpo[LARGO_CADENA] = {'\0'}; /* cadena estatica para el cuerpo del mensaje */

    datos = (Datos*) parametros; /* asigno el puntero datos al puntero parametros */
    inicializar_mensaje(&entrada); /* incializa los valores del mensaje */ 

    recibir_mensaje(datos->id_cola_mensaje, MSG_CABALLO + datos->id, &entrada);
    /* espera a recibir el mensaje de parte del Hipodromo para empezar a correr */

    if(entrada.evento == EVT_INICIO) {
        printf("Empieza la carrera - Caballo %d Listo\n", datos->id + 1);
        jugar = 1; /* que empiece el juego */
        /*metros_al_disco = atoi(entrada.cuerpo);  pedido en el enunciado, no se usa. Por eso lo comento*/
    }

    printf("Caballos corriendo...\n");
    
    /*mientras jugar = 1 */
    while(jugar) {

        metros_recorridos += numeroAleatorio (METROS_MIN, METROS_MAX); /* acumula metros aleatorios */
        sprintf(cuerpo, "%d", metros_recorridos);

        /* le manda mensaje al hipodromo con los metros acumulados y espera saber si gano*/
        enviar_mensaje(datos->id_cola_mensaje, MSG_HIPODROMO, MSG_CABALLO + datos->id, EVT_METROS, cuerpo);
        /* espera mensaje*/
        recibir_mensaje(datos->id_cola_mensaje, MSG_CABALLO + datos->id, &entrada);

        switch (entrada.evento) {
        case EVT_SIGA:
            /*en caso de que SIGA, espera el tiempo indicado en enunciado*/
            usleep(numeroAleatorio(ESPERA_MIN, ESPERA_MAX) *1000);
            break;

        case EVT_CRUZARON_EL_DISCO:
            /* si es el ganado, lo guarda en sus datos */
            if(atoi(entrada.cuerpo) == datos->id) {
                datos->ganador = datos->id;
            }
            jugar = 0;
            break;
        
        default:
            break;
        }
    }
    /* el retorno del ganador lo hago mediante datos porque en los apuntes inica que no se debe usar el pthread_exit para retornar valores obtenidos en el thread, que solo es de estado. */ 

    /* finaliza el hilo */
    pthread_exit((void*)"listo");
}

int jugar(pthread_t *caballo, int cant_caballos, int id_cola_mensajes) {

    int i = 0;
    Datos *datos; /*variable dinamica de tipo Datos para pasar los parametros a los hilos */

    /* dimesiono la memoria dinamica datos */
    datos = (Datos*) malloc (sizeof(Datos) * cant_caballos);

    for(i = 0; i < cant_caballos; i++) {
        /* incializo datos*/
        datos[i].id = i;
        datos[i].id_cola_mensaje = id_cola_mensajes;
        datos[i].ganador = -1; /* -1 porque existe el caballo 0, y luego me daria 2 ganadores */

        if(crear_thread(&caballo[i], caballoThread, &datos[i]) == -1) {
            printf("Error al crear el hilo");
            free(datos); /*en caso de error, libero la memoria dinamica datos*/
            return -1;
        }
    }
    /* espera que todos los hilos terminen */
    for (i = 0; i < cant_caballos; i ++) {
        esperar_thread(caballo[i]);

        /* mira si el caballo [i] es el ganador, comparando el dato.ganador.*/
        if(datos[i].ganador == datos[i].id){
            printf("\nEl ganador es el caballo %d\n", i+1);
        }
    }

    free(datos); /* libero memoria dinamica datos */

    /*el hipodrmo espera este mensaje antes de terminar y liberar todo*/
    enviar_mensaje (id_cola_mensajes, MSG_HIPODROMO, MSG_CABALLO, EVT_NINGUNO, "listo"); 

    return 0;
}
