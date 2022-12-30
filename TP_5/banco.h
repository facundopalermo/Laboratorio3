#ifndef __BANCO_H
#define __BANCO_H

    #include <time.h>
    #include "./common/global.h"

    #define CLIENTES 100 //cantidad de clientes, definido por el enunciado

    typedef struct banco {
        int cliente;
        int saldo;
    } Banco;

    int aleatorio (int desde, int hasta);
    void iniciar_banco(Banco *banco, Cajero *cajeros, int cant_cajeros);
    int validar_cliente (int id_cliente, Banco *banco);
    void procesar_operacion(Mensaje buzon, Banco *banco, int id_cola_mensaje);

#endif