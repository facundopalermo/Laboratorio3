#ifndef __MENSAJE_H
#define __MENSAJE_H

    #include <sys/msg.h>
    #include <string.h>
    #include "clave.h"

    #define LARGO_MENSAJE 1024
    #define TOTAL 100
    #define CLAVE_BASE 33

    typedef struct tipo_mensaje{

        long long_dest;  
        int int_rte;  
        int int_evento;  
        char char_mensaje[LARGO_MENSAJE];  

    }mensaje;

    int creo_id_cola_mensajes(int);
    void liberar_cola(int Id_Cola_Mensajes);
    int recibir_mensaje(int, long , mensaje*);
    int enviar_mensaje(int, long, int, int, char*);

    int borrar_mensajes(int id_cola_mensajes);
#endif    