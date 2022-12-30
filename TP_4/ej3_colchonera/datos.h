#ifndef __DATOS_COLCHONERA_H
#define __DATOS_COLCHONERA_H

    #define LARGO_NOMBRE 10 //10 porque suavestar que es el mas largo tiene 9 letras
    #define CANTIDAD 5 // se requieren 5 registros

    typedef struct descripcion {
        int codigo;
        int cantidad;
        char nombre[LARGO_NOMBRE];
    }Colchones;


#endif
