#include "../headers/jugadores_f.h"

void *hiloJugador(void *parametros) {

    Dato *dato; /*puntero para obtener los datos de la memoria dinamica creada en la linea 55. No requiere dimensionar*/
    Mensaje mensaje;
    int empezar = 0;
    char cuerpo[LARGO_CADENA];

    dato = (Dato *) parametros; /*obtengo los datos pasados al crear el hilo*/

    while (empezar == 0) { /*espera mensaje de incio para empezar a jugar*/

        recibir_mensaje(dato->id_cola_msg, MSG_JUGADOR + dato->id, &mensaje);

        if (mensaje.evento == EVT_INICIO) {
            empezar = 1;
        }
    }

    pthread_mutex_lock(&mutex); /*semaforo mutex para que cada jugadr lo haga de a una vez*/

        if (*dato->disparo < CANT_JUGADORES) { /*verifica que no se pasa de rosca*/
            printf("Soy el jugador %d y voy a dispararme! \n", dato->id + 1); /*id+1 para que se vea del 1 al 6*/

            dato->vector_tambor[*dato->disparo] = 1; /*dispara, y pone la recamara en 1*/
            (*dato->disparo)++; /*gira el tambor y aumenta el indice para el proximo jugador*/
            sprintf(cuerpo, "%d", *dato->disparo); /*le paso ese valor al revolver, ya que tambien usa indices (bala) del 1 al 6*/

            printf("Soy el jugador %d y la posicion del tambor es %d! \n", dato->id + 1, *dato->disparo); /*idem linea 28*/
            enviar_mensaje(dato->id_cola_msg, MSG_REVOLVER, MSG_JUGADOR + dato->id, EVT_DISPARO, cuerpo); /* golpea martillo ...*/ 
        }

        recibir_mensaje(dato->id_cola_msg, MSG_JUGADOR + dato->id, &mensaje); /*... y espera resultados...*/

        if (mensaje.evento == EVT_SALVADO) { /*si no habia bala, se salva y lo informa*/
            printf("Jugador %d suspira... \n\n", dato->id+1);
            strcpy(cuerpo, "Me salvé!");
        } else if (mensaje.evento == EVT_FIN && atoi(mensaje.cuerpo)==dato->id) { /*lamentablemnte muere, no puede decir nada*/
            printf("-(x_x)-> (RIP Jugador %d)\n\n", dato->id+1);
            strcpy(cuerpo, "Eliminado");
        } else {
            printf("Jugador %d suspira... \n\n", dato->id+1); /*otro jugador acaba de morir, lo festeja*/
            strcpy(cuerpo, "Me salvé de jugar!");
        }

    pthread_mutex_unlock(&mutex);

    strcpy(dato->mensaje, cuerpo);

    pthread_exit((void*) cuerpo);
}

int jugar(pthread_t *jugador, int *vector_tambor, int id_cola_msg) {

    int i = 0;
    Dato *dato; /*memoria dinamica se dimensiona en linea 60 y se libera en linea 81*/
    int disparo = 0;
    
    dato = (Dato *)malloc(sizeof(Dato) * CANT_JUGADORES);

    for (i = 0; i < CANT_JUGADORES; i++) { /*inicializa datos y crea los hilos*/

        dato[i].id = i; /*id del jugador*/
        dato[i].vector_tambor = vector_tambor; /*vector del tambor que viene desde el main*/
        dato[i].id_cola_msg = id_cola_msg;
        dato[i].disparo = &disparo; /*indice para saber cual es la siguiente recamara del vector tambor*/

        if(crearThread(&jugador[i], hiloJugador, &dato[i]) == -1){
            return -1;
        }
    }

    sleep(1); /*tiempo para que que todos los jugadores terminen de hacer lo suyo y no se superpongan los mensajes*/

    for(i = 0; i < CANT_JUGADORES; i++) { /*hago el join (esperarThread) y muestra el resultado del juego*/
        pthread_join(jugador[i], (void **) 0);
        printf("Jugador %d dice: %s\n", i+1, dato[i].mensaje);
    }

    free(dato);
    return 0;
}