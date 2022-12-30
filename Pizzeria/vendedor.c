#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vendedor_f.h"
#include "./common/memcomp.h"
#include "./common/mensaje.h"
#include "./common/global.h"
#include "./common/semaforo.h"

int main(int argc, char const *argv[]) {
    
    int id_memcomp = 0;
    int id_cola_mensaje = 0;
    int id_semaforo = 0;
    int abrir = 0;
    Pizzeria *pizzas_hechas;

    srand(time(0));

    pizzas_hechas = (Pizzeria*)crear_memoria(&id_memcomp, (sizeof(Pizzeria) * PIZZEROS), ARCHIVO_BASE, CLAVE_BASE);
    
    if((id_cola_mensaje = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE)) == -1) {
        return limpiar(pizzas_hechas, id_memcomp, id_cola_mensaje);
    }

    if ((id_semaforo = crear_semaforo (ARCHIVO_BASE, CLAVE_BASE)) == -1) {
        return limpiar(pizzas_hechas, id_memcomp, id_cola_mensaje);
    }else {
        iniciar_semaforo(id_semaforo, VERDE);
    }

    borrar_mensajes(id_cola_mensaje);

    do {
        printf("Para abrir el local ingrese 1: ");
        if(scanf("%d", &abrir) == 0){
            printf("Error en el uso de scanf o el valor ingresado no es un numero\n");
            return limpiar(pizzas_hechas, id_memcomp, id_cola_mensaje);
        }
    }while(abrir != 1);

    printf("Bienvenidos!\n");
    abrir_local(pizzas_hechas, id_cola_mensaje, id_semaforo);

    calcular_resultado(pizzas_hechas);

    return limpiar(pizzas_hechas, id_memcomp, id_cola_mensaje);
}

