#include <stdlib.h>
#include <stdio.h>
#include <time.h> /* para el srand */
#include <sys/types.h> /* para el pthread_t, ya que no se requiere toda la libreria de pthread.h */

#include "./headers/caballos_f.h" /* funciones del juego */
#include "./headers/global.h" /* Constantes, validar_caballo().. */
#include "./headers/mensaje.h"

int main(int argc, char const *argv[]) {
    
    int cant_caballos= 0; /*variable para almacenar la cantidad de caballos, recibida por parametros*/
    int id_cola_mensajes = 0; /*id de la cola de mensaje*/
    pthread_t *caballo; /*variable dinamica de tipo phtread_t para clear los hilos */

    /* verifico los valores ingresados por el usuario al ejecutar el programa */
    /* debe tener por lo menos dos caballos */
    if((cant_caballos = validar_caballos (argc, argv)) == -1) {
        printf("Solo se admite un parametro y la cantidad de caballos ingresada debe ser mayor a 2\n");
        return -1;
    }
    /*inicializo semilla para random*/
    srand(time((void*)0));

    /* inicio la cola de mensaje, y borra los mensajes */
    id_cola_mensajes = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE);

    /* dimensiono la variable dinamica */
    caballo = (pthread_t*) malloc (sizeof(pthread_t) * cant_caballos);

    printf("Presione enter para comenzar...\n");
    printf("Comenzará cuando haga enter en ambos procesos...\n");
    scanf("enter");

    /* funcion principal */
    if (jugar(caballo, cant_caballos, id_cola_mensajes) == -1) {
        free(caballo); /* ante fallo al crear hilo, libero la memoria dinamica */
        return -1;
    }
    
    /* la cola de mensaje se libera en el proceso hipodromo */
    
    free(caballo); /*libera memoria dinamica*/
    return 0;
}
