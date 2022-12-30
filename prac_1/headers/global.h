#ifndef __GLOBAL_H
#define __GLOBAL_H
    
    #define CLAVE_BASE 33
    #define LARGO 1000 /*para definir cadenas*/
  
    typedef enum{

        MSG_NADIE,
        MSG_BOLERA,
        MSG_JUGADOR
    }Destinos;

    typedef enum{

        EVT_NINGUNO,
        EVT_INICIO, 
        EVT_TIRO,
        EVT_RESULTADO,
        EVT_FIN


    }Eventos; 


    int aleatorio(int desde, int hasta);



#endif