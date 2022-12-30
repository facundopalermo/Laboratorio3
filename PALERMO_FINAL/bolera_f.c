#include <stdio.h>
#include <stdlib.h>

#include "./headers/bolera_f.h"
#include "./headers/mensaje.h"
#include "./headers/global.h"

void jugar(int id_cola_mensajes, int cant_jugadores) {

    /*Lineas es una estructura que contiene todos los datos de la linea: jugador, pinos, intentos.. */
    Linea *lineas;
    int i = 0;
    int jugador = 0;
    int pinos_tirados = 0;
    int jugar = 0;
    Mensaje entrada;
    char cuerpo[LARGO_CADENA] = {'\0'};

    /* se libera al final */
    lineas = (Linea *) malloc (sizeof(Linea)*cant_jugadores);

    inicializar_mensaje(&entrada);

    for(i = 0; i < cant_jugadores; i++) {
        lineas[i].jugador = i + 1;
        lineas[i].intentos = 0;
        lineas[i].pinos = 10;
        lineas[i].puntos = 0;
    }

    /* da incio a cada jugador */
    for(i = 0; i < cant_jugadores; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_BOLERA, EVT_INICIO, "nada");
    }

    /* jugar es un contador que aumenta a medida que los jugadores terminan */
    while(jugar < cant_jugadores) {
        recibir_mensaje(id_cola_mensajes, MSG_BOLERA, &entrada);

        jugador = entrada.remitente - MSG_JUGADOR;

        /* el switch no es necesario, pero me parece apropiado para la estructura del codigo, pero podria ser un if o nada en si. */
        switch (entrada.evento) {
        case EVT_TIRO:

            /*calcula los pinos tirados por el jugador y los guarda */
            pinos_tirados = numeroAleatorio(1, lineas[jugador].pinos);
            lineas[jugador].pinos = lineas[jugador].pinos - pinos_tirados;
            lineas[jugador].intentos++;
            
            /* Muestra mensaje de chuza si el aleatorio es 10 y da 20 puntos */
            if(pinos_tirados == 10) {
                printf("CHUZA\n");
                lineas[jugador].puntos = 20;
            } else {
                /* caso contrario, suma puntos segun los pinos tirados */
                lineas[jugador].puntos += pinos_tirados;
            }

            /* cuando se alcanzan los 3 intentos o tira todos los pinos termina el juego para ese jugador */
            if(lineas[jugador].intentos == 3 || lineas[jugador].pinos == 0) {
                sprintf(cuerpo, "%d", lineas[jugador].puntos);
                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + jugador, MSG_BOLERA, EVT_FIN, cuerpo);
                jugar += 1;
            } else {
                /* caso contrario envia la cantidad de pinos tirados */
                sprintf(cuerpo, "%d", pinos_tirados);
                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + jugador, MSG_BOLERA, EVT_RESULTADO, cuerpo);
            }
            break;
        default:
            break;
        }
    }
    /* libera la memoria dinamica creada */
    free(lineas);
}
