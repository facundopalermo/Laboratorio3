#ifndef __CONTROL_F_
#define __CONTROL_F_
    typedef struct tipo_control{

        int id_cola_mensajes; 
        int *ganador; 
        int *estacionamiento;

    }Control;

    int jugar(int id_cola_mensajes);
    void *hiloControl(void *parametros);

   

#endif