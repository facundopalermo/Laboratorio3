#include <stdio.h>
#include <stdlib.h>
#include "../common/global.h"
#include "bomba.h"

//funcion que inicializa el vector de bombas
void iniciar_juego(Bomba *bombas, int cant_arti){

    for (int i=0; i < cant_arti; i++){
        bombas[i].numero_artificiero = i+1;
        bombas[i].cableSeleccionado = 0;
        bombas[i].estado_bomba = 2;
    }

}

// funcion principal que se encarga de verificar si el artificiero adivinó el cable
int procesar_bombas (Bomba *bombas, int artificiero, int cable_desactiva, Resultado *resultado) {

    int i = artificiero;
    int evaluar = 1; //inicializo en 1, ya que es la condicion de seguir evaluando.

    //si el artificiero "i" cortó un cable (estado 0)
    if (bombas[i].estado_bomba == 0) {
        //verifico si es el cable correcto
        if (bombas[i].cableSeleccionado == cable_desactiva){
            //si lo es, cambio el estado a desactivada (1)
            bombas[i].estado_bomba = 1;
            //evaluar=0 para dejar de evaluar
            evaluar = 0;
            //guardo cual artificiero fue el que adivinó
            resultado->ultimo_artif = i;
            resultado->contar_intentos++; //cuento el acierto tambien como un intento
        
        //caso contrario
        } else {
            //disminuyo la cantidad de intentos y cuento los intentos
            resultado->cantidad_intentos--;
            resultado->contar_intentos++;

            //si la cantidad de intentos es 0, la bomba explota
            if (resultado->cantidad_intentos == 0) {
                bombas[i].estado_bomba = 3; //explota
                evaluar = 0; //dejo de evaluar
                resultado->ultimo_artif = i; //el que la hizo explotar
                printf("Explotó\n");
            //si aun hay intentos, pongo el estado en 2 para que pueda volver a intentar
            } else {
                bombas[i].estado_bomba = 2;
            }
        }
    }

    return evaluar;
}