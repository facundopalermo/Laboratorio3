#ifndef __VENDEDOR_H
#define __VENDEDOR_H
    #define PIDE_CODIGO "Ingrese un codigo de producto (1 a 5): "
    #define ERROR_CODIGO "El codigo debe estar comprendido entre 1 y 5.\n"
    #define PIDE_CANTIDAD "Ingrese la cantidad a vender: "
    #define ERROR_CANTIDAD "La cantidad indicada supera la cantidad disponible."
    #define VENTA_CANCELA "Cantidad ingresada menor a 1, se ha cacelado la venta."
    #define VENTA_EXITO "Venta registrada con exito!\n"

    void vender_colchon(Colchones *stock);
#endif