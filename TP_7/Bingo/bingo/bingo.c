#include "../headers/bingo.h"

int main(int argc, char const *argv[]) {
    
    int cant_jugadores = 0;
    int ganador = 0; /*variable a la que se le asignará el ganador desde la funcion jugar*/
    int id_cola_msg;
    int id_memcomp;
    int *inicio; /*memoria compartida que se requiere en 1 para iniciar el bingo*/

    pthread_t bolillero;

    srand(time((void*) 0));

    if ((cant_jugadores = validarJugadores(argc, argv)) == -1 ) { /*funcion que valida los argumentos*/
        return (-1);
    }
    id_cola_msg = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);
    inicio = (int*) crear_memoria(&id_memcomp, sizeof(int), ARCHIVO_BASE,CLAVE_BASE); /*se libera en linea 36*/

    if(*inicio == 1) { /*el proceso jugadores asigna 1 cuando se incia*/
        printf("Hola Jugadores! a Jugar!..\n");
        borrar_mensajes(id_cola_msg);

        if ((ganador = jugar(&bolillero, cant_jugadores, id_cola_msg)) == -1) { /*funcion principal que retorna al ganador*/
            printf("Hubo un error. El juego se acabó.\n"); /*si existe un error, finaliza*/
            return (-1);
        }

        printf("\nEl ganador del bingo es el jugador %d. Felicitaciones!\n\n", ganador + 1);
    } else {
        printf("Antes de comenzar, deben llegar los jugadores.\n");
    }

    liberar_cola_mensajes(id_cola_msg);
    liberar_memoria(inicio, id_memcomp);
    printf("Gracias por venir, vuelva pronto!\n");
    return 0;
}
