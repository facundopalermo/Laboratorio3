#ifndef __BANCO_H
#define __BANCO_H

    #include "./common/global.h"

    int iniciar_cajero (void);
    int dame_id_cliente(void);
    int dame_operacion(void);
    int dame_importe(void);
    void procesar_operacion(int id_cliente, int operacion, int id_cola_mensaje, int cajero);
    void procesar_respuesta(Mensaje mensaje);

#endif