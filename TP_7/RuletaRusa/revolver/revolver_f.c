#include "../headers/revolver_f.h"

int cargar_bala(int desde, int hasta) { 
    return rand() % (hasta - desde + 1) + desde;
}

void empezar (int id_cola_msg) {

    int i = 0;

    for (i = 0; i < CANT_JUGADORES; i++) {
        enviar_mensaje(id_cola_msg, MSG_JUGADOR + i, MSG_REVOLVER, EVT_INICIO, "nada");
    }
    
}

void ruleta_rusa(int *bala, int id_cola_msg) {

    Mensaje mensaje;
    int jugador = 0;
    int gatillada = 0;
    int i = 0;
    char eliminado[LARGO_CADENA];

    while ( (*bala) != 0) { /*la bala cambiará a 0 cuando haya sido disparada*/
        
        recibir_mensaje(id_cola_msg, MSG_REVOLVER, &mensaje); /*recibe mensajes de los jugadores*/

        if (mensaje.evento == EVT_DISPARO) { /*si es por el disparo...*/

            jugador = mensaje.remitente - MSG_JUGADOR;
            gatillada = atoi(mensaje.cuerpo); /*obtiene cual recamara fue gatillada*/

            if ((*bala) == gatillada ) { /*si la bala fue gatillada, Bang!*/
                (*bala) = 0;
                printf("Bang!\n");
                
                sprintf(eliminado, "%d", jugador);

                for (i = 0; i < CANT_JUGADORES; i++) { /* y avisa a todos los jugadores que quien fue eliminado*/
                    enviar_mensaje(id_cola_msg, MSG_JUGADOR + i, MSG_REVOLVER, EVT_FIN, eliminado);
                }
                
            } else { /*caso contrario, la recamara estaba vacía y solo se escucha el martillo golpear nada, Tik!*/
                printf("Tik!\n");
                enviar_mensaje(id_cola_msg, MSG_JUGADOR + jugador, MSG_REVOLVER, EVT_SALVADO, "nada"); /*le avisa a ese jugador que se salvó*/
            }
        }
    }
}