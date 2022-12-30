#ifndef __MENSAJE_H
#define __MENSAJE_H

    #include <sys/msg.h>
    #include <string.h>
    #include "clave_recurso.h"
    
    #define LARGO_CADENA 1024

    typedef struct mensaje {
        long destinatario;
        int remitente;
        int evento;
        char cuerpo[LARGO_CADENA];
    }Mensaje;

    int crear_cola_mensaje(char *archivo_clave, int clave_base);
    int enviar_mensaje(int id_cola_msg, long destino, int remitente, int evento, char* cuerpo);
    int recibir_mensaje(int id_cola_msg, long destino, Mensaje *entrada);
    int borrar_mensajes(int id_cola_msg);
    void liberar_cola_mensajes(int id_cola_mensajes);

#endif