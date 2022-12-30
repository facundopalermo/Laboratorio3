#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#include "vendedor_f.h"
#include "./common/global.h"
#include "./common/mensaje.h"
#include "./common/semaforo.h"
#include "./common/memcomp.h"


void abrir_local(Pizzeria *pizzas_hechas, int id_cola_mensaje, int id_semaforo) {
    int i = 0, j = 0;
    int cantidad = 0;
    int pide_cliente = 0;
    int pizzero = 0;
    int eleccion = 0;
    Mensaje entrada;
    int comanda[MENU] = {0};
    char cuerpo[LARGO_CADENA];

    /*inicializo pizzas_hechas*/
    espera_semaforo(id_semaforo);
        for(i = 0; i < PIZZEROS; i++) {
            pizzas_hechas[i].pizzero = i;
            for (j = 0; j < MENU; j++) {
                pizzas_hechas[i].pizzas[j] = 0;
            }
        }
    levanta_semaforo(id_semaforo);

    while (cantidad < PIZZAS_MAX) {

        pide_cliente = numeroAleatorio(1, 3);
        pizzero = numeroAleatorio(0, 2);

        printf("Cliente pidió %d pizzas\n", pide_cliente);

        espera_semaforo(id_semaforo);
            for(i = 0; i < pide_cliente; i++) {
                eleccion = numeroAleatorio(0,4);
                comanda[eleccion]++;
            }
            cantidad+=pide_cliente;
        levanta_semaforo(id_semaforo);

        sprintf(cuerpo,"%d|%d|%d|%d|%d", comanda[0],comanda[1],comanda[2],comanda[3],comanda[4]);

        enviar_mensaje(id_cola_mensaje, MSG_PIZZERO + pizzero, MSG_VENDEDOR, EVT_PIZZA, cuerpo);
        printf("Pedido enviado a pizzero %d\n", pizzero + 1);

        for(i = 0; i < MENU; i++) {
            comanda[i] = 0;
        }

        printf("\nEsperando otro cliente...\n");
        usleep(numeroAleatorio(CLIENTE_CADA_DESDE, CLIENTE_CADA_HASTA) * 100);
    }

    for(i = 0; i < PIZZEROS; i++) {
        enviar_mensaje(id_cola_mensaje, MSG_PIZZERO + i, MSG_VENDEDOR, EVT_CERRAR, "cerrar");
    }
    printf("Esperando pizzeros para cerrar...\n");
    recibir_mensaje(id_cola_mensaje, MSG_VENDEDOR, &entrada);
}

void calcular_resultado(Pizzeria *pizzas_hechas) {
    int i = 0, j = 0;
    int cantidad = 0;
    int total_parcial = 0, total = 0;

    for (i = 0; i < PIZZEROS; i++) {
        printf("Pizzero %d:\n", i+1);
        for (j = 0; j < MENU; j++) {

            cantidad = pizzas_hechas[i].pizzas[j];

            switch ( j ){
            case MUZZARELLA:
                total_parcial = cantidad * PRECIO_MUZZARELLA;
                printf("\tMuzzarella x %d = $ %d\n", cantidad, total_parcial);
                break;
            case CALABRESA:
                total_parcial = cantidad * PRECIO_CALABRESA;
                printf("\tCalabresa x %d = $ %d\n", cantidad, total_parcial);
                break;
            case PRIMAVERA:
                total_parcial = cantidad * PRECIO_PRIMAVERA;
                printf("\tPrimavera x %d = $ %d\n", cantidad, total_parcial);
                break;
            case ANCHOAS:
                total_parcial = cantidad * PRECIO_ANCHOAS;
                printf("\tAnchoas x %d = $ %d\n", cantidad, total_parcial);
                break;
            case NAPOLITANA:
                total_parcial = cantidad * PRECIO_NAPOLITANA;
                printf("\tNapolitana x %d = $ %d\n", cantidad, total_parcial);
                break;
            default:
                break;
            }

            total += total_parcial;
        }
        printf("\n");
    }

    printf("Total recaudado: %d\n", total);
}

int limpiar (Pizzeria *pizzas_hechas, int id_memcomp, int id_cola_mensaje) {
    liberar_memoria(pizzas_hechas, id_memcomp);
    liberar_cola_mensajes(id_cola_mensaje);
    return 1;
}