#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./common/global.h"
#include "./common/memcomp.h"
#include "./common/mensaje.h"
#include "./common/semaforo.h"
#include "pizzero_f.h"

int main(int argc, char const *argv[]) {

    int id_memcomp = 0;
    int id_cola_mensaje = 0;
    int id_semaforo = 0;
    Pizzeria *pizzas_hechas;
    
    srand(time(0));

    pizzas_hechas = (Pizzeria*)crear_memoria(&id_memcomp, (sizeof(Pizzeria) * PIZZEROS), ARCHIVO_BASE, CLAVE_BASE);
    
    if((id_cola_mensaje = crear_cola_mensaje(ARCHIVO_BASE, CLAVE_BASE)) == -1) {
        return -1;
    }

    if ((id_semaforo = crear_semaforo (ARCHIVO_BASE, CLAVE_BASE)) == -1) {
        return -1;
    }

    borrar_mensajes(id_cola_mensaje);

    if(cocinar (pizzas_hechas, id_cola_mensaje, id_semaforo) == -1) {
        return -1;
    }

    return 0;
}
