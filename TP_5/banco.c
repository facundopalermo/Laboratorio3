#include "banco.h"

int main(int argc, char const *argv[]) {
        
    Banco *banco; // Variable para 100 clientes (podría ser estática, pero la hice dinámica)
    Cajero *cajeros; // para generar el "listado" de cajeros que se van a conectar
    Mensaje mensaje;

    int id_cola_mensaje;
    int id_semaforo;
    int id_memoria;
    int contador_cajeros = 0; // indice para conocer el proximo cajero

    int operaciones_diarias = 0; //solo es para cortar el bucle while

    id_cola_mensaje = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);
    id_semaforo = crear_semaforo(ARCHIVO_BASE, CLAVE_BASE);
    iniciar_semaforo(id_semaforo, VERDE);

    cajeros = (Cajero*)crear_memoria(&id_memoria, sizeof(Cajero)*CANT_CAJEROS, ARCHIVO_BASE, CLAVE_BASE);

    srand(time(NULL));
    banco = (Banco*) malloc (sizeof(Banco)*CLIENTES);

    //inicializa las cuentas de los clientes y el struct de cajeros
    iniciar_banco(banco, cajeros, CANT_CAJEROS);

    //simplememente para no hacer un bucle infinito. En 5 operaciones cierra el banco.
    while (operaciones_diarias < MAX_OPERACIONES) {

        /* aqui consulta si se conecta un nuevo cajero y lo informa */
        espera_semaforo(id_semaforo);
            if (cajeros[contador_cajeros].iniciado == 1){
                printf("Se ha inciado el cajero %d.\n", cajeros[contador_cajeros].id);
                contador_cajeros++;
            }
        levanta_semaforo(id_semaforo);

        //A la espera de que algun cajero envie un mensaje, y cuando llega, se procesa
        printf("\nEsperando operacion en cajeros automaticos...\n");
        recibir_mensaje(id_cola_mensaje, BANCO, &mensaje);
        
        printf("Procesando operacion...\n");
        procesar_operacion(mensaje, banco, id_cola_mensaje);

        operaciones_diarias++; 
    }

    /*libera la cola de mensajes, la memoria compartida y la dinamica.*/
    liberar_cola_mensajes(id_cola_mensaje);
    liberar_memoria(cajeros, id_memoria);
    free(banco);
    printf("\nEl banco ha cerrado. Hasta pronto.\n");
    return 0;
}