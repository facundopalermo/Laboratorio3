#include "../headers/jugadores_f.h"

/*funcion que genera el carton del jugador*/
void escogerCarton(int carton[]) {
    int i = 0;
    for( i = 0; i < N_CARTON; i++ ) {
        carton[i] = numeroSinRepetir(N_MIN, N_MAX, carton);
    }
}

/* Funcion que muestra el carton luego de escogerlo*/
void mostrarCarton(int carton[], int jugador) {
    int i = 0;
    printf("Carton del jugador %d:\t", jugador + 1);
    for (i = 0; i < N_CARTON; i++) {
        printf("[%.2d] ", carton[i]);
    }
    printf("\n");
}

/*Funcion que busca el numero que salió en el bombo, y lo busca en su carton*/
int mirarCarton(int bolilla, int carton[]) {
    return buscaNumero(bolilla, N_CARTON, carton);
}

void * threadJugador (void * parametros) {

    Datos *datos; /*puntero para parametros*/
    Mensaje mensaje;
    int bolilla = 0; /*para la bolilla recibida por mensaje*/
    int i = 0;
    int jugar = 1;
    char cuerpo[LARGO_CADENA];
    int carton[N_CARTON] = {0};

    datos = (Datos*)parametros;

    escogerCarton(carton); /*escoge un carton entre los muchos que se podrían generar!*/

    /*priorizo el hilo para mostrar el carton y no se mezclen los numeros*/
    pthread_mutex_lock(&mutex);
        mostrarCarton(carton, datos->id); /*muestra carton*/
    pthread_mutex_unlock(&mutex);

    while( jugar == 1) { /*condicion de corte, cambia a 0 con EVT_CARTON_LLENO*/

        recibir_mensaje(datos->id_cola_msg, MSG_JUGADOR + datos->id, &mensaje);

        switch (mensaje.evento) {
            case EVT_BOLILLA:
                /*cuando mira la bolilla, si coincide con su carton, lo marca y suma un acierto*/
                bolilla = atoi(mensaje.cuerpo);
                if (mirarCarton(bolilla, carton) == 1) {
                    datos->aciertos ++;

                    printf("Jugador %d acertó el número %d\n", datos->id+1, bolilla);
                    printf("\t - Jugador %d dice: me faltan %d números!\n\n", datos->id+1, N_CARTON - datos->aciertos);

                    /*si llega a los N_CARTON aciertos, BINGO!*/
                    if(datos->aciertos == N_CARTON) {
                        printf("\nJugador %d dice: BINGO!!\n\n", datos->id + 1);
                        for(i = 0; i < datos->cant_jugadores; i++) {
                            /*y lo notifica al proceso bingo y a los otros jugadores (incluido el mismo)*/
                            enviar_mensaje(datos->id_cola_msg, MSG_BINGO, MSG_JUGADOR + datos->id, EVT_CARTON_LLENO, cuerpo);
                            enviar_mensaje(datos->id_cola_msg, MSG_JUGADOR + i, MSG_JUGADOR + datos->id, EVT_CARTON_LLENO, cuerpo);
                        }
                    }
                }
            break;

            case EVT_CARTON_LLENO:
                jugar = 0;
            break;
        }
    }

    pthread_exit((void *) "listo");
}

int jugar(pthread_t * jugadores, int cant_jugadores, int id_cola_msg) {

    Datos *datos; /*se dimensiona en linea 82*/
    int i = 0;

    datos = (Datos*) malloc (sizeof(Datos) * cant_jugadores); /*se libera en linea 101*/

    for(i = 0; i < cant_jugadores; i++) {

        datos[i].id = i;
        datos[i].id_cola_msg = id_cola_msg;
        datos[i].aciertos = 0;
        datos[i].cant_jugadores = cant_jugadores;
        
        if ((crearThread(&jugadores[i], threadJugador, &datos[i])) == -1) {
            return -1;
        }
    }

    for(i = 0; i < cant_jugadores; i++) {
        esperarThread(jugadores[i]);
        printf("Jugador %d: %d aciertos.\n", datos[i].id + 1, datos[i].aciertos);
    }

    free(datos);
    return 0;
}