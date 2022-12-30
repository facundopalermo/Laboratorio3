#ifndef __MENSAJE_H
#define __MENSAJE_H


    #define LARGO_MENSAJE 1024


    typedef struct tipo_mensaje{

        long long_dest;  
        int int_rte;  
        int int_evento;  
        char char_mensaje[LARGO_MENSAJE];  

    }Mensaje;

    int creo_id_cola_mensajes(int);
    void liberar_cola(int Id_Cola_Mensajes);
    int recibir_mensaje(int, long , Mensaje*);
    int enviar_mensaje(int, long, int, int, char*);

    int borrar_mensajes(int id_cola_mensajes);

#endif    