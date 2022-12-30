#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>

#define ROJO 0
#define VERDE 1
#define CLAVE_BASE 77
#define ARCHIVO_LOTE "lote.dat"

// ESTRUCTURA PARA DATOS
typedef struct pasaje {
    int vuelo;
    char destino[85];
    char nombre[100];
} Pasaje;

int crear_semaforo ();
void iniciar_semaforo (int id_semaforo, int valor);
void levanta_semaforo (int id_semaforo);
void espera_semaforo (int id_semaforo);
const char*  getDestino (int vuelo);
int cargarvuelos (Pasaje pasajes[]);


// FUNCIONES PARA MANEJO DE SEMAFOROS

key_t crear_clave (int r_clave) {
    key_t clave;
    clave = ftok ("/bin/ls", r_clave);
    if ( clave == (key_t) -1) {
        printf ("Error: No se pudo obtener clave para recurso compartido\n");
        exit(0);
    }
    return clave;
}

int crear_semaforo () {
    key_t clave = crear_clave(CLAVE_BASE);
    int id_semaforo = semget(clave, 1, 0600|IPC_CREAT);
    if ( id_semaforo == -1 ) {
        printf ("Error al crear el semaforo\n");
        exit(0);
    }
    return id_semaforo;
}

void iniciar_semaforo (int id_semaforo, int valor) {
    semctl(id_semaforo,0 , SETVAL, valor);
}

void levanta_semaforo (int id_semaforo) {
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = 1;
    operacion.sem_flg = 0;
    semop (id_semaforo, &operacion, 1);
}

void espera_semaforo (int id_semaforo) {
    struct sembuf operacion;
    printf("El sistema está esperando acceso al archivo... \n");
    operacion.sem_num = 0;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;
    semop (id_semaforo, &operacion, 1);
}

// FUNCIONES DE UTILIDAD
const char*  getDestino (int vuelo) {
    switch (vuelo){
    case 1000:
        return "MEXICO";
    case 1001:
        return "ARGENTINA";
    case 1002:
        return "COLOMBIA";
    case 1003:
        return "URUGUAY";
    case 1004:
        return "CHILE";
    case 1005:
        return "VENEZUELA";
    case 1006:
        return "PERU";
    case 1007:
        return "ECUADOR";
    case 1008:
        return "MALVINAS";
    case 1009:
        return "BOLIVIA";
    case 1010:
        return "ANTARTIDA";
    default:
        break;
    }
}
/*
void salir() {
    printf("Gracias por usar el sistema de carga de pasajes...\n");
    printf("Tenga un gran día!\n");
    exit(EXIT_SUCCESS);
}
*/
int cargarvuelos (Pasaje pasajes[]) {

    int vuelo = 1;
    char destino [85]={'\0'};
    char persona [100]={'\0'};
    int cont = 0;
    
    printf("\nIngrese numero de vuelo: ");
    scanf("%d", &vuelo);
    while ( (vuelo < 1000 || vuelo > 1010) && (vuelo != 0) ) {
        printf("El vuelo debe ser mayor o igual a 1000 o menor o igual a 1010\n");
        printf("Ingese numero de vuelo: ");
        scanf("%d", &vuelo);
        while(getchar()!='\n');
    }

    while ( vuelo != 0 ) {
        printf("Ingrese nombre del pasajero: ");
        scanf("%s", persona);
        while(getchar()!='\n');

        pasajes[cont].vuelo = vuelo;
        strcpy(pasajes[cont].destino, getDestino(vuelo));
        strcpy(pasajes[cont].nombre, persona);

        cont++;

        printf("Ingrese numero de vuelo: ");
        scanf("%d", &vuelo);
        while ( (vuelo < 1000 || vuelo > 1010) && (vuelo != 0) ) {
            printf("El vuelo debe ser mayor o igual a 1000 o menor o igual a 1010\n");
            printf("Ingese numero de vuelo: ");
            scanf("%d", &vuelo);
            while(getchar()!='\n');
        }
    }

    return cont;
}

int main (void) {

    FILE *archivo;
    Pasaje pasajes[100]={0};
    int cantidad=0;

    int id_semaforo = crear_semaforo();
    iniciar_semaforo(id_semaforo, VERDE);
    
    while(1){

        cantidad = cargarvuelos(pasajes);

        if (cantidad > 0){
            
            espera_semaforo(id_semaforo);

                if ((archivo = fopen(ARCHIVO_LOTE, "a")) == NULL ){
                    printf("Error: no se pudo abrir lote.dat");
                } else {
                    for (int i = 0; i < cantidad ; i++){
                        fprintf (archivo, "%d %s %s\n", pasajes[i].vuelo, pasajes[i].destino, pasajes[i].nombre);
                    }

                    fclose(archivo);
                    printf("... Lote guadado.\n");

                }

            levanta_semaforo(id_semaforo);
        }
    }

    return 0;
}