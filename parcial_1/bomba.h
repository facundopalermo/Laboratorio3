#ifndef __F_BOMBA_H
#define __F_BOMBA_H

    #define ESPERA 100
    
    typedef struct resultado{
        int ultimo_artif;
        int cantidad_intentos;
        int contar_intentos;
    }Resultado;
    
    void iniciar_juego(Bomba *bombas, int cant_arti);
    int procesar_bombas (Bomba *bombas, int artificiero, int cable_desactiva, Resultado *resultado);
    
#endif