#include "banco.h"

//Genera numero aleatorio: lo usa el banco para generar los saldos de las cuentas
int aleatorio (int desde, int hasta) {
    return rand() % (hasta - desde + 1) + desde;
}

//inicializa las cuentas de los clientes y el struct de cajeros
void iniciar_banco(Banco *banco, Cajero *cajeros, int cant_cajeros) {

    for(int i = 0; i < CLIENTES; i++) {
        banco[i].cliente = ( i + 1 );
        banco[i].saldo = aleatorio(0, 1000);
    }

    for(int i = 0; i < cant_cajeros; i++) {
        cajeros[i].id = (i+1);
        cajeros[i].iniciado = 0;
    }
}

int validar_cliente (int id_cliente, Banco *banco) {
    //podria hacer verificar si el id está comprendido entre 1 y 100, pero quise hacerlo así por si llegara a usar ids random en otra oportunidad
    for (int i = 0; i < CLIENTES; i++) {
        if (banco[i].cliente == id_cliente) {
            return 1;
        }
    }

    return -1;
}

//
void procesar_operacion (Mensaje buzon, Banco *banco, int id_cola_mensaje) {

    int id_cliente = -1;
    int evento = -1;
    int importe = 0;
    char cuerpo[LARGO_CADENA];

    printf("Operacion desde cajero: %d\n", (int)buzon.destinatario);

    /*
    switch de Eventos (operaciones). En caso de error, lo retorna por mensaje
    El mensaje se arma y envia al final de la funcion
    en cada case se arma el cuerpo del mensaje. todos con formato %d|%d
    Ademas se imprime por pantalla, la operacion realizada
    siendo que conozco el formato de respuesta, es que par strtok no usé while
    */
    switch (buzon.evento)
    {
    case EVT_CONSULTA_SALDO:

        id_cliente = atoi(buzon.cuerpo)-1;

        if(validar_cliente(id_cliente + 1, banco) == -1){
            evento = EVT_RTA_SALDO_NOK;
            sprintf(cuerpo, "%d|%d", id_cliente + 1, ERR_CLIENTE_NOT_FOUND);
            printf("Operacion cancelada -> cliente %d no existe.\n", id_cliente + 1);
        } else {
            evento = EVT_RTA_SALDO;
            sprintf(cuerpo, "%d|%d", id_cliente + 1, banco[id_cliente].saldo);
            printf("Operacion exitosa -> cliente %d consulta saldo.\n", id_cliente + 1 );
        }

        break;

    case EVT_DEPOSITO:

        id_cliente = atoi(strtok(buzon.cuerpo,"|"))-1;
        importe = atoi(strtok(NULL,"|"));

        if(validar_cliente(id_cliente + 1, banco) == -1){
            evento = EVT_RTA_DEPOSITO_NOK;
            sprintf(cuerpo, "%d|%d", id_cliente + 1, ERR_CLIENTE_NOT_FOUND);
            printf("Operacion cancelada -> cliente %d no existe.\n", id_cliente + 1);
        } else if (importe < 1){
            evento = EVT_RTA_DEPOSITO_NOK;
            sprintf(cuerpo, "%d|%d", id_cliente + 1, ERR_MONTO_INCORRECTO);
            printf("Operacion cancelada -> cliente %d ingreso monto incorrecto.\n", id_cliente + 1);
        } else {
            banco[id_cliente].saldo += importe;
            evento = EVT_RTA_DEPOSITO_OK;
            sprintf(cuerpo, "%d|%d", id_cliente + 1, banco[id_cliente].saldo);
            printf("Operacion exitosa -> cliente %d hizo deposito de %d.\n", id_cliente + 1, importe);
        }

        break;

    case EVT_EXTRACCION:

        id_cliente = atoi(strtok(buzon.cuerpo,"|"))-1;
        importe = atoi(strtok(NULL,"|"));

        if(validar_cliente(id_cliente + 1, banco) == -1){
            evento = EVT_RTA_EXTRACCION_NOK;
            sprintf(cuerpo, "%d|%d", id_cliente + 1, ERR_CLIENTE_NOT_FOUND);
            printf("Operacion cancelada -> cliente %d no existe.\n", id_cliente + 1);
        } else if (importe > banco[id_cliente].saldo){
            evento = EVT_RTA_EXTRACCION_NOK;
            sprintf(cuerpo, "%d|%d", id_cliente + 1, ERR_SALDO_INSUFICIENTE);
            printf("Operacion cancelada -> cliente %d intenta retirar mas dinero del que tiene.\n", id_cliente + 1);
        } else {
            banco[id_cliente].saldo -= importe;
            evento = EVT_RTA_EXTRACCION_OK;
            sprintf(cuerpo, "%d|%d", id_cliente + 1, banco[id_cliente].saldo);
            printf("Operacion exitosa -> cliente %d extrajo %d de su cuenta.\n", id_cliente + 1, importe);
        }
       
        break;
    }
    
    //armo y envio mensaje
    enviar_mensaje(id_cola_mensaje, buzon.destinatario, BANCO, evento, cuerpo);
}