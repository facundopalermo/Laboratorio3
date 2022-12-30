#include <stdlib.h>
#include <stdio.h>
#include <time.h> /* para el srand */

#include "./headers/hipodromo_f.h" /*contiene las funciones del hipodromo*/
#include "./headers/global.h" /* para las constantes de ARCHIVO_BASE y CLAVE_BASE y validar_caballos() */
#include "./headers/mensaje.h"

int main(int argc, char const *argv[]) {

    int cant_caballos= 0; /*variable para almacenar la cantidad de caballos, recibida por parametros*/
    int id_cola_mensajes = 0; /*id de la cola de mensaje*/

    /* verifico los valores ingresados por el usuario al ejecutar el programa */
    /* debe tener por lo menos dos caballos */
    if((cant_caballos = validar_caballos (argc, argv)) == -1) {
        printf("Solo se admite un parametro y la cantidad de caballos ingresada debe ser por lo menos de 2\n");
        return -1;
    }

    /*inicializo semilla para random*/
    srand(time((void*)0));

    printf("Abre el hipodromo!\n");
    printf("Presione enter para comenzar...\n");
    printf("Comenzará cuando haga enter en ambos procesos...\n");
    scanf("enter");

    /* inicio la cola de mensaje, y borra los mensajes */
    id_cola_mensajes = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);

    /* funcion principal */
    jugar (cant_caballos, id_cola_mensajes);

    /* finalizada la carrera, se libera la cola de mensaje*/
    liberar_cola_mensajes(id_cola_mensajes);
    printf("Hipodromo cerrado.\n");
    
    return 0;
}
