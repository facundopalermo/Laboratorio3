#include "cajero.h"

int main(int argc, char const *argv[]){

    int cajero = 1;
    int id_cola_mensaje = -1;
    Mensaje mensaje;

    if ((cajero = iniciar_cajero()) == 0){
        printf("Error. Debe abrir primero el banco.\n");
        exit(EXIT_FAILURE);
    }

    id_cola_mensaje = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);

    while ( 1 ) {

        printf("\nBienvenido!. Ingrese su tarjeta...\n");
        procesar_operacion(dame_id_cliente(), dame_operacion(), id_cola_mensaje, cajero);

        printf("\nAguardando datos del banco...\n");
        recibir_mensaje(id_cola_mensaje, cajero, &mensaje);

        if(strpbrk(mensaje.cuerpo, "|") == NULL) { 
            /*
            si el banco aun no abrió, la respuesta solo será el id del cliente
            todas las respuestas deben contener id_cliente|algo
            NOTA: esto se ejecutaba cuando habia solo un cajero.
            La condicion que cierra el programa si es que no inició el banco está antes, cuando inciar_cajero()
            */
            printf("El banco se encuentra cerrado. Vuelva mas tarde.\n");
            liberar_cola_mensajes(id_cola_mensaje);
            exit(EXIT_FAILURE);
        }

        procesar_respuesta(mensaje);

    }
    
    return 0;
}
