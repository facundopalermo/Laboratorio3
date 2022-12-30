#include <stdio.h>
#include <stdlib.h>
#include "datos.h"
#include "vendedor.h"

//funcion que se encarga de realizar la venta
void vender_colchon(Colchones *stock) {

    int codigo_a_vender = 0;
    int cantidad_a_vender = 0;
    
    printf("%s", PIDE_CODIGO);
    scanf("%d", &codigo_a_vender);
    while ((codigo_a_vender < 1) || (codigo_a_vender > 5)){
    //si el codigo es menor a 1 o mayor a 5, pido otra vez el codigo
        printf("\n%s%s", ERROR_CODIGO, PIDE_CODIGO);
        scanf("%d", &codigo_a_vender);
    }
    codigo_a_vender--; // -1 para obtener el indice real

    printf("%s", PIDE_CANTIDAD);
    scanf("%d", &cantidad_a_vender);

    while( stock[codigo_a_vender].cantidad < cantidad_a_vender ){
    //si no hay stock pido nuevo valor e indico el stock actual
        printf("\n%s %s %d\n",ERROR_CANTIDAD, "stock actual:", stock[codigo_a_vender].cantidad);
        printf("%s", PIDE_CANTIDAD);
        scanf("%d", &cantidad_a_vender);
    }

    if ( cantidad_a_vender < 1 ) {
        // si cantidad es menor a 1, se cancela la venta
        printf("%s\n", VENTA_CANCELA);
    } else {
        //caso contrario, resto la cantidad vendida al stock
        stock[codigo_a_vender].cantidad = stock[codigo_a_vender].cantidad - cantidad_a_vender;
        printf("%s\n", VENTA_EXITO);
    }

}
