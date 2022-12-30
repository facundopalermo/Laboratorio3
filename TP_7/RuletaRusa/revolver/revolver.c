#include "../headers/revolver.h"

int main(int argc, char const *argv[]) {
    
    int bala;
    int id_cola_msg;

    srand(time((void*) 0));

    id_cola_msg = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);
    borrar_mensajes(id_cola_msg);

    bala = cargar_bala(1, 6); /*bala random*/
    printf("Bala en la recámara %d... Gira el tambor...\n", bala);

    empezar(id_cola_msg); /*funcion que se encarga de enviar el EVT_INICIO a todos los jugadores*/
    printf("Quien será el primero...\n");

    ruleta_rusa(&bala, id_cola_msg); /*funcion que se encarga de recibir los mensajes y procesar los gatillos*/

    /*para dar tiempo a todos los jugadores y no se elimine antes la cola de mensajes*/
    sleep(1);

    liberar_cola_mensajes(id_cola_msg);

    return 0;
}
