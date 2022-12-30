#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "./headers/jugadores_f.h"
#include "./headers/threads.h"
#include "./headers/mensaje.h"
#include "./headers/global.h"
#include "./headers/semaforo.h"

void * jugadorThread (void * parametros) {

    Datos *datos;
    Mensaje entrada;
    int jugar = 0;
    int pinos_tirados = 0;

    datos = (Datos*) parametros;
    inicializar_mensaje(&entrada);

    /* espera a recibir el mensaje de inicio */
    recibir_mensaje(datos->id_cola_mensaje, MSG_JUGADOR + datos->id, &entrada);

    /*si bien es el primer mensaje y no es necesario el if, lo uso para cambiar el valor de jugar = 1 */
    if(entrada.evento == EVT_INICIO) {
        jugar = 1;
    }

    while (jugar) {
        
        /* el semaforo es meramente para el sincronismo siguiendo las recomendaciones del profesor, ya que no se requiere en este ejercicio como medio para bloquear acceso a recursos compartidos */
        
        espera_semaforo(datos->id_semaforo);
            /* envia mensaje de tiro y espera el resultado por parte de la bolera */
            printf("Soy el jugador %d y voy a tirar...\n", datos->id+1);
            enviar_mensaje(datos->id_cola_mensaje, MSG_BOLERA, MSG_JUGADOR + datos->id, EVT_TIRO, "tiro");

            recibir_mensaje(datos->id_cola_mensaje, MSG_JUGADOR + datos->id, &entrada);

            /* en base a lo que informe la bolera, se procesa y muestra los datos.. */
            switch (entrada.evento) {
            case EVT_RESULTADO:
                pinos_tirados = atoi(entrada.cuerpo);
                printf("Soy el jugador %d y tiré %d bolos\n", datos->id+1, pinos_tirados);
                break;
            /* cuando recibe EVT_FIN, cambia a jugar = 0 y sale del bucle */
            case EVT_FIN:
                datos->puntos = atoi(entrada.cuerpo);
                jugar = 0;
                break;

            default:
                break;
            }

        levanta_semaforo(datos->id_semaforo);
        usleep(ESPERA * 1000);
    }

    pthread_exit((void*)"listo");
}

int jugar(int id_cola_mensajes, int cant_jugadores, pthread_t *jugador ) {

    Datos *datos;
    int id_semaforo = 0;
    int i = 0;

    /* dimensiono la memoria dinamica datos */
    datos = (Datos*) malloc (sizeof(Datos) * cant_jugadores);
    id_semaforo = crear_semaforo (ARCHIVO_BASE, CLAVE_BASE);
    iniciar_semaforo(id_semaforo, VERDE);

    for(i = 0; i < cant_jugadores; i++) {
	/*inicializo datos a pasar a los hilos y creo los hilos */
        datos[i].id = i;
        datos[i].id_cola_mensaje = id_cola_mensajes;
        datos[i].puntos = 0;
        datos[i].id_semaforo = id_semaforo;

        if(crearThread(&jugador[i], jugadorThread, &datos[i]) == -1) {
            free(datos);
            return -1;
        }
    }
    
    /* espera a los hilos */
    for(i = 0; i < cant_jugadores; i++) {
        esperarThread(jugador[i]);
        printf("El jugador %d hizo %d puntos.\n", datos[i].id+1, datos[i].puntos);
    }

    /* libera datos. los hilos se liberan en main */
    free(datos);
    return 0;
}
