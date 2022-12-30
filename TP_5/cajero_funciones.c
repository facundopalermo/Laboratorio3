#include "cajero.h"

/*
funcion que se encarga de generar el id para el cajero.
accede a la memoria compartida iniciada en el banco, y busca el primer id no iniciado.
*/
int iniciar_cajero () {
    int id_semaforo = -1;
    int id_memoria = -1;
    int id_cajero = 1;

    Cajero *cajeros = NULL;
    id_semaforo = crear_semaforo(ARCHIVO_BASE, CLAVE_BASE);
    cajeros = (Cajero*)crear_memoria(&id_memoria, sizeof(Cajero)*CANT_CAJEROS, ARCHIVO_BASE, CLAVE_BASE);
    
    espera_semaforo(id_semaforo);

        for(int i = 0; i < CANT_CAJEROS; i++){
            if (cajeros[i].iniciado == 0){
                
                id_cajero = cajeros[i].id;
                cajeros[i].iniciado = 1;
                printf("cajero: %d\n", cajeros[i].id);

                // encontrado un no iniciado, levanta el semaforo y retorna el valor.
                levanta_semaforo(id_semaforo);
                return id_cajero;
            }
        }
    //si ya no hay cajeros disponibles, levanta el semaforo y cierra el proceso.
    levanta_semaforo(id_semaforo);
    printf("Ya se han iniciado todos los cajeros. El programa finalizará\n");
    exit(EXIT_FAILURE);
}

//funcion que pide cliente
int dame_id_cliente() {

    int id_cliente = -1;

    do {
        printf("Ingrese su id de cliente: ");
        if(scanf("%d", &id_cliente) != 1) {
            printf("Error al leer entrada\n");
        }
    }while (id_cliente <= 0);

    return id_cliente;
}

//funcion que pide operación
int dame_operacion() {

    int operacion = 0;

    do {
        printf("Seleccione la operacion que desea realizar:\n");
        printf("1. Consulta de Saldo\n");
        printf("2. Deposito\n");
        printf("3. Extracción\n");
        printf("Su eleccion: \n");

        if(scanf("%d", &operacion) != 1){
            printf("Error al leer entrada\n");
        }
    }while (operacion < 1 && operacion > 3);

    return operacion;
}

//si se necesita, funcion que pide importe
int dame_importe() {

    int importe = 0;

    do {
        printf("Ingrese el importe: ");
        if (scanf("%d", &importe) != 1) {
            printf("Error al leer entrada\n");
        }
    }while (importe <= 0);

    return importe;
}

/*
Funcion simple que crea el cuerpo del mensaje y lo manda.
Aprovechando que enviar_mensaje retorna -1 cuando no logra enviar el mensaje, esto es porque el banco cerró
(se eliminó la cola de mensajes), entonces, cancelo la operacion y cierra el proceso
*/
void procesar_operacion(int id_cliente, int operacion, int id_cola_mensaje, int cajero) {

    char cuerpo[LARGO_CADENA];
    int evento = -1;

    switch (operacion){
    case 1:
        evento = EVT_CONSULTA_SALDO;
        sprintf(cuerpo,"%d", id_cliente);
        break;

    case 2:
        evento = EVT_DEPOSITO;
        sprintf(cuerpo,"%d|%d", id_cliente, dame_importe());
        break;

    case 3:
        evento = EVT_EXTRACCION;
        sprintf(cuerpo,"%d|%d", id_cliente, dame_importe());
        break;

    }

    /*si se acabaron las operaciones en el banco, la cola se libera,
    y por lo tanto no podrá enviar el mensaje, caso contrario, todo sigue su curso*/
    if (enviar_mensaje(id_cola_mensaje, cajero, BANCO, evento, cuerpo) == -1){
        printf("No es posible realizar esta operacion en este momento. Por favor regrese cuando abra el banco.\n");
        exit(EXIT_FAILURE);
    }
}

//funcion que procesa las respuestas enviadas por el banco
void procesar_respuesta(Mensaje mensaje) {

    int cliente_id = -1;
    int respuesta = -1;

    cliente_id = atoi(strtok(mensaje.cuerpo, "|"));
    respuesta = atoi(strtok(NULL, "|"));

    switch (mensaje.evento){
        case EVT_RTA_SALDO:
            printf("Cliente %d: Su saldo actual es de %d.\n", cliente_id, respuesta);
            break;
        case EVT_RTA_SALDO_NOK:
            if(respuesta == ERR_CLIENTE_NOT_FOUND) {
                printf("No existe registro del cliente %d en este banco.\n", cliente_id);
            }
            break;

        case EVT_RTA_DEPOSITO_OK:
            printf("Cliente %d: Deposito exitoso. Su saldo actual es de %d.\n", cliente_id, respuesta);
            break;

        case EVT_RTA_DEPOSITO_NOK:
            if(respuesta == ERR_CLIENTE_NOT_FOUND) {
                printf("No existe registro del cliente %d en este banco.\n", cliente_id);
            }else if(respuesta == ERR_MONTO_INCORRECTO){
                //este error es inutil, porque no permito enviar valores negativos, igual lo puse.
                printf("El monto ingresado es incorrecto. Debe ser un numero positivo.\n");
            }
            break;

        case EVT_RTA_EXTRACCION_OK:
            printf("Cliente %d: extraccion exitosa. Su saldo actual es de %d.\n", cliente_id, respuesta);
            break;

        case EVT_RTA_EXTRACCION_NOK:
            if(respuesta == ERR_CLIENTE_NOT_FOUND) {
                printf("No existe registro del cliente %d en este banco.\n", cliente_id);
            }else if(respuesta == ERR_SALDO_INSUFICIENTE){
                printf("No fue posible realizar la operacion. Su saldo es insuficiente.\n");
            }
            break;
    }

}
