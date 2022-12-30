#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../common/semaforo.h"
#include "../common/memcomp.h"
#include "../common/global.h"
#include "../common/funciones.h"
#include "bomba.h"

int main(int argc, char const *argv[]){
    
    int cant_cables = 0;
    int cant_artificieros = 0;
    int cable_desactiva = 0;
    int cantidad_intentos = 0;

    int evaluar = 1;

    int id_semaforo = -1; //inicializo en -1 porque es el valor que podria retornar si hay error al crear_semaforo
    int id_memoria = -1; //inicializo en -1 porque es el valor que podria retornar si hay error al crear_memoria

    Bomba *bombas = NULL; //puntero que apunta a un tip Bomba (dato)
    //Resultado *resultado; //estructura que uso para guardar el conteo de intentos, el ultimo artificiero, y el conteo inverso de intentos
    Resultado resultado;
    srand(time(NULL)); //inicia semilla para aleatorios diferentes

    if (argc == 3) {
        //evaluo los parametros
        cant_cables = atoi(argv[1]);
        cant_artificieros = atoi(argv[2]);

    } else {
        printf("Debe inciar el programa con 2 parametros:\n");
        printf("./bomba cant_cables cant_artificieros\n");
        exit(EXIT_FAILURE);
    }

    if(cant_cables < 1 || cant_artificieros < 1){
        printf("La cantidad de cables y la cantidad de artificieros deben ser mayor a 1\n");
        exit(EXIT_FAILURE);
    }

    //inicializo las variables indicadas con su correspndiente aleatorio
    cable_desactiva = aleatorio(1, cant_cables);
    cantidad_intentos = aleatorio(1, cant_cables);

    //creo e inicio semaforo
    id_semaforo = crear_semaforo(ARCHIVO_BASE, CLAVE_BASE);
    iniciar_semaforo(id_semaforo, VERDE);

    //asigno el puntero bomba al espacio obtenido con la funcion crear_memoria
    bombas = (Bomba*)crear_memoria(&id_memoria, sizeof(Bomba)*cant_artificieros,ARCHIVO_BASE,CLAVE_BASE);

    //dimenciono la estructura dinamica resultado ... ESTO FUE LO QUE ME FALTÓ en el parcial, y por eso un 4...
    //resultado = (Resultado*) malloc(sizeof(Resultado));

    //incicializo el struct de resultado
    /*
    resultado->contar_intentos = 0;
    resultado->ultimo_artif = 0;
    resultado->cantidad_intentos = cantidad_intentos;*/
    resultado.contar_intentos = 0;
    resultado.ultimo_artif = 0;
    resultado.cantidad_intentos = cantidad_intentos;

    //inicializo las "bombas" (la memoria compartida)
    iniciar_juego(bombas, cant_artificieros);

    printf("Esperando jugadores...\n");

    //evaluar == 1 es equivalente a true. cando es 0 (false), deja de evaluar y termina el programa.
    while ( evaluar == 1 ) {

        espera_semaforo(id_semaforo);

        //seccion critica

            //recorro el vector de bombas y proceso cada uno.
            for (int i = 0; i < cant_artificieros; i++){
                evaluar = procesar_bombas(bombas, i, cable_desactiva, &resultado);
                if (evaluar == 0){
                    break; //si procesar bombas explotó o se desactivó, dejo de recorrer el for
                }
            }

            //verifico si explotó o no y muestro los resultados, caso contrario continua evaluando.
            if(evaluar == 0 && resultado.cantidad_intentos>0) {
                printf("El artificiero %d gano en %d intentos\n", bombas[resultado.ultimo_artif].numero_artificiero, resultado.contar_intentos);
            }else if (evaluar == 0 && resultado.cantidad_intentos == 0){
                printf("La bomba le explotó al artificiero %d\n", bombas[resultado.ultimo_artif].numero_artificiero);
            }
        
        //fin seccion critica
        levanta_semaforo (id_semaforo);
        usleep(ESPERA*1000); //espera 100ms
    }
    printf("Gracias por jugar\n");
    liberar_memoria(bombas, id_memoria); //libero la memoria creada en bombas. Lo hace solo este proceso.
    //free(resultado);// y Hay que liberar esa memoria dnamica...
    return 0;
}