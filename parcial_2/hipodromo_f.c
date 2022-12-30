#include <stdlib.h>
#include <stdio.h>

#include "./headers/hipodromo_f.h"
#include "./headers/global.h" /*contiene definiones y la funcion de aleatorio*/
#include "./headers/mensaje.h" /* funciones de mensaje */

void jugar (int cant_caballos, int id_cola_mensajes) {

    int i = 0;
    int metros_al_disco = 0; /* variable que contendrá la distancia total de recorrido */ 
    int metros_recorridos = 0; /* variable para guardar los metros recorridos por un caballo */
    int caballo = 0; /* indice para arrays */
    int jugar = 1; /* bandera para el while */
    Tabla *tabla_caballos; /*memoria dinamica para guardar los id y recorridos de los caballos*/
    Tabla *tabla_aux; /*memoria dinamica para ordenar los id y recorridos de los caballos*/
    /*uso una tabla auxiliar, para no desordenar la original ya que accedo a ella mediante el indice caballo */

    char cuerpo[LARGO_CADENA] = {'\0'}; /* cadena estatica para el cuerpo del mensaje */
    Mensaje entrada; /* estrucutra de mensaje para recibirlos */

    tabla_caballos  =(Tabla*) malloc (sizeof(Tabla) * cant_caballos); /*dimensiono dinamica tabla_caballo*/
    
    metros_al_disco = numeroAleatorio(RECORRODO_MIN, RECORRIDO_MAX); /* establece mediante random, la cantidad de metros*/

    tabla_aux = (Tabla*) malloc (sizeof(Tabla) * cant_caballos); /*dimensiono memoria dinamica tabla_aux*/

    inicializar_mensaje(&entrada); /*funcion que inicializa las variables detro de la estructura Mensaje*/

    /*inicializa tabla_caballos*/
    for (i = 0; i < cant_caballos; i++) {
        tabla_caballos[i].id = i;
        tabla_caballos[i].metros_recorridos = 0;
        tabla_aux[i].id = i;
        tabla_aux[i].metros_recorridos = 0;
    }

    sprintf(cuerpo, "%d", metros_al_disco); /*preparo el cuerpo del mensaje con la cantidad de metros de la pista*/

    /*envia el mensaje de inicio a todos los caballos */
    for(i = 0; i < cant_caballos; i++) {
        enviar_mensaje(id_cola_mensajes, MSG_CABALLO + i, MSG_HIPODROMO, EVT_INICIO, cuerpo);
    }

    /* comienza el juego, termina cuando jugar = 0 */
    while(jugar) {

        recibir_mensaje(id_cola_mensajes, MSG_HIPODROMO, &entrada);
        /* espera recibir mensaje y lo procesa */

        if (entrada.evento == EVT_METROS) {
           /* si el evento es EVT_METROS */ 
            
            caballo = entrada.remitente - MSG_CABALLO; /* obtengo el indice del caballo */
            metros_recorridos = atoi(entrada.cuerpo); /* obtengo los metros recorridos */

            tabla_caballos[caballo].metros_recorridos = metros_recorridos; /* los guarda en la tabla */ 

            if (metros_recorridos >= metros_al_disco) {
                /*si se alcanza la meta, prepara el mensaje para todos los demas caballos y lo manda*/
                
                sprintf(cuerpo, "%d", caballo);
                for(i = 0; i < cant_caballos; i++) {
                    enviar_mensaje(id_cola_mensajes, MSG_CABALLO + i, MSG_HIPODROMO, EVT_CRUZARON_EL_DISCO, cuerpo);
                    jugar = 0; /* cambia la bandera par salir del bucle */
                }

            } else {
                /* caso contrario le dice al caballo remitente, que siga corriendo */
                enviar_mensaje (id_cola_mensajes, MSG_CABALLO + caballo, MSG_HIPODROMO, EVT_SIGA, "siga");
            }
            /* muestro las posiciones de cada jugador, mediante el ordenamiento (burbuja) de la tabla_aux */
            printf("\nLargo de la pista: %d\n", metros_al_disco);
            mostrar_posiciones(tabla_caballos, tabla_aux, cant_caballos);

        }
    }
    
    /* con este while se deshace los mensajes que podrian haber quedado para este proceso y espera recibir un mensaje para finalizar. Usé EVT_NINGUNO para no crear otro evento y no ir contra el enunciado.*/
    /*tambien podria usar memoria compartida o señales, pero me parecio mejor usar algo ya implementado (mensaje)*/
    while(1) {
        recibir_mensaje(id_cola_mensajes, MSG_HIPODROMO, &entrada);
        if(entrada.evento == EVT_NINGUNO) {
            printf("\nCerrando...\n");
            break;
        }
    }

    /* libera las dos memorias dinamicas creadas */
    free (tabla_caballos);
    free(tabla_aux);
}

void mostrar_posiciones (Tabla *tabla_caballos, Tabla *tabla_aux, int cant_caballos) {

    int i = 0;
    
    /* copia los valores de la tabla original a la auxiliar */
    /* no cree la tabla auxiliar en esta funcion para no estar dimensionando y liberando en cada iteracion de la carrera */
    for(i = 0; i < cant_caballos; i++) {
        tabla_aux[i].id = tabla_caballos[i].id;
        tabla_aux[i].metros_recorridos = tabla_caballos[i].metros_recorridos;
    }
    
    ordenar(tabla_aux, cant_caballos); /*ordena la estructura auxiliar por medio del metodo burbuja*/

    /* imprime en consola los puestos, de mejor a peor, ya que la burbuja ordena de menor a mayor */
    for(i = (cant_caballos-1); i >= 0; i--) {
        printf("%d. Caballo %d -> %d metros.\n", cant_caballos-i, tabla_aux[i].id + 1, tabla_aux[i].metros_recorridos);
    }
}

/*ordena el auxiliar por medio del metodo burbuja */
void ordenar (Tabla *tabla_aux, int n) {

    int i = 0, j = 0;
    Tabla aux; /*memoria estatica auxiliar para hacer los intercabios */
    aux.id = 0; /* inicializo los valores */
    aux.id = 0;
    
    /*el metodo burbuja ordena comparando el valor con los siguientes, haciendo flotar al mayor */
    for(i = 0 ; i < n; i++ ){
        for (j = 0; j < n-1; j++){
            if(tabla_aux[j].metros_recorridos > tabla_aux[j+1].metros_recorridos){
                /* si es mayor, guardo el valor en el auxiliar */
                aux.id = tabla_aux[j+1].id;
                aux.metros_recorridos = tabla_aux[j+1].metros_recorridos;
                /* pongo el vaor en el siguiente lugar */
                tabla_aux[j+1].id = tabla_aux[j].id;
                tabla_aux[j+1].metros_recorridos = tabla_aux[j].metros_recorridos;
                /* y recupero el valor anterior guardado */
                tabla_aux[j].id = aux.id;
                tabla_aux[j].metros_recorridos = aux.metros_recorridos;
            }
        }
    }
}
