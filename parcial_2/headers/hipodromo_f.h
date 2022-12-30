#ifndef __HIPODROMO_F_H
#define __HIPODROMO_F_H

    #define RECORRODO_MIN 800
    #define RECORRIDO_MAX 1000

    typedef struct tabla_caballos
    {
        int id;
        int metros_recorridos;
    }Tabla;
    
    void jugar (int cant_caballos, int id_cola_mensajes);
    void mostrar_posiciones (Tabla *tabla_caballos, Tabla *tabla_aux, int cant_caballos);
    void ordenar (Tabla *vector, int n);

#endif
