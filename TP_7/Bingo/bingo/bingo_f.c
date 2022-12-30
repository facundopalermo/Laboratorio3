#include "../headers/bingo_f.h"

void * threadBolillero (void * parametros) {

    Datos *datos;
    int bolillero[N_MAX] = {0};
    int bolilla = 0;
    int i = 0;
    char cuerpo[LARGO_CADENA];

    datos = (Datos*) parametros;

    /* la condicion  (bolilla < N_MAX) no es necesaria ya que siempre habrá un ganador y nunca pasará el indice N_MAX*/
    while (datos->ganador == 0) {
        bolillero[bolilla] = numeroSinRepetir(N_MIN, N_MAX, bolillero);
        sprintf(cuerpo, "%d", bolillero[bolilla]);

        printf("\nGira el bombo y la bolilla %d es... %d!\n", bolilla + 1, bolillero[bolilla]);
        bolilla ++;
        
        /* muestra la bolilla a los jugadores*/
        for(i = 0; i < datos->cant_jugadores; i++){
            enviar_mensaje(datos->id_cola_msg, MSG_JUGADOR + i, MSG_BINGO, EVT_BOLILLA, cuerpo);
        }

        usleep((numeroAleatorio(T_MIN, T_MAX)) * 1000);
    }

    pthread_exit((void *) "listo");
}

int jugar(pthread_t *bolillero, int cant_jugadores, int id_cola_msg) {

    int ganador = 0;
    Datos datos;
    Mensaje mensaje;

    datos.cant_jugadores = cant_jugadores;
    datos.ganador = 0;
    datos.id_cola_msg = id_cola_msg;

    if ((crearThread(bolillero, threadBolillero, &datos)) == -1) {
        return (-1);
    }
    /*el main espera algun ganador*/
    if (recibir_mensaje(id_cola_msg, MSG_BINGO, &mensaje) == -1) {
        perror("Hubo un error al recibir el mensaje. Error: ");
        return (-1);
    }
    /*cuando se recibe el mensaje (aunque es el unico EVT posible) */
    if(mensaje.evento == EVT_CARTON_LLENO) { 
        ganador = mensaje.remitente - MSG_JUGADOR;
        datos.ganador = ganador;
    }

    sleep(1); /*1 segundo para que los jugadores terminen sus tareas*/
    return ganador;
}