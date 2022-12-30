#include "./headers/bolera_f.h"
#include "./headers/global.h"
#include "./headers/mensaje.h"
#include "./headers/semaforos.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>

void jugar(int id_cola_mensajes, int cant_jugadores)
{

    int *vector;
    int i = 0;
    char mensaje[LARGO] = {'\0'};
    int done = 0;
    int nro_jugador = 0, pinos_tirados = 0, pinos_disponibles = 0;
    Mensaje msg;
    Bolera *bolera;
    int puntos = 0;

    bolera = (Bolera *)malloc(sizeof(Bolera) * cant_jugadores); /*mem dinamica para bolera*/
    vector = (int *)malloc(sizeof(int) * cant_jugadores);       /*mem dinamica para vector*/

    for (i = 0; i < cant_jugadores; i++)
    { /*le envia a todos*/

        vector[i] = 10; /*incializo con 10 pinos*/
        bolera[i].nro = i;
        bolera[i].cant_tiros = 0;

        printf("BOLERA %d cant %d\n", i + 1, vector[i + 1]);

        memset(mensaje, 0, LARGO); /*incializo siempre q voy a pasar un mensaje */
        sprintf(mensaje, "%d", i);
        enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + i, MSG_BOLERA, EVT_INICIO, mensaje);
    }

    while (done < cant_jugadores)
    {

        recibir_mensaje(id_cola_mensajes, MSG_BOLERA, &msg); /*espera recibir mensaje */

        if (msg.int_evento == EVT_TIRO)
        {

            nro_jugador = msg.int_rte - MSG_JUGADOR;
            pinos_disponibles = vector[nro_jugador]; /*primero veo cuando pinos me quedan*/

            bolera[nro_jugador].cant_tiros += 1; /*actualizo cant tiros*/

            printf("Jugador %d, pinos disponibles %d\n", nro_jugador + 1, pinos_disponibles);

            pinos_tirados = aleatorio(1, pinos_disponibles);
            printf("QUE %d %d\n", nro_jugador, pinos_tirados);
            vector[nro_jugador] = pinos_disponibles - pinos_tirados; /*actualizo */

            for (i = 0; i < cant_jugadores; i++)
            { /*visualizar bolera*/
                printf("[%d]\t", vector[i]);
            }

            if (pinos_tirados == 10)
            { /*tire todos*/

                printf("CHUZA %d\n", pinos_disponibles);
                puntos = 20;
            }
            else
            {
                puntos = pinos_tirados;
            }

            memset(mensaje, 0, LARGO); /*inicializo*/
            sprintf(mensaje, "%d", puntos);

            if (vector[nro_jugador] == 0 || bolera[nro_jugador].cant_tiros == 3)
            {
                /*termina segun tiros o si tiro todos*/

                done += 1; /*para terminar */
                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + nro_jugador, MSG_BOLERA, EVT_FIN, mensaje);
            }
            else
            {

                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR + nro_jugador, MSG_BOLERA, EVT_RESULTADO, mensaje);
            }
        }
        usleep(1000 * 1000);

    }

    printf("Termina\n");
    free(bolera);
    free(vector);
    printf("FIN\n");
}
