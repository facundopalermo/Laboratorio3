#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <time.h>

#define CLAVE_BASE 77
#define MAX_CAJEROS 3
#define VERDE 1
#define ROJO 0

typedef struct movimiento{
    int importe;
    int tipo; // 0 cheque | 1 efectivo
} Movimiento;


// FUNCIONES DE SEMAFORO

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
    operacion.sem_num = 0;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;
    semop (id_semaforo, &operacion, 1);
}

int generaAleatorio (int idesde, int ihasta){
    return (rand() % (ihasta - idesde + 1) + idesde);
}

int generarLote (Movimiento movimiento []) {
    int tam = generaAleatorio(10,20);

    for (int i = 0; i < tam; i++) {
        movimiento[i].importe = generaAleatorio(100, 500);
        movimiento[i].tipo = generaAleatorio(0,1);
    }

    return tam;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int cajero = 0;
    int trabajar = 0;
    char nombre_archivo[12];
    int tamanio_lote = 0;
    int espera_mcs=0;

    Movimiento movimientos[20] = {0};

    FILE *archivo;

    int id_semaforo = crear_semaforo();
    iniciar_semaforo(id_semaforo, VERDE);
    
    if (argc == 2){
        cajero = atoi(argv[1]);
        if (cajero < 1 || cajero > MAX_CAJEROS){
            printf("El argumento debe estar compredido entre 1 y %d\n", MAX_CAJEROS);
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Ejecute el programa indicando el numero del cajero como parametro (e.g.: ./cajero 1)\n");
        exit(EXIT_FAILURE);
    }

    sprintf(nombre_archivo,"cajero%d.dat", cajero);
    int cont=0;
    while(1){

        trabajar = generaAleatorio(1,3);
        printf("Cajero %d esperando cliente...\n", cajero);

        if ( trabajar == cajero ){            

            espera_semaforo(id_semaforo);

                if ((archivo = fopen(nombre_archivo, "a")) == NULL ){
                    printf("Error: no se pudo abrir %s\n", nombre_archivo);
                } else {

                    tamanio_lote = generarLote(movimientos);

                    for (int i = 0; i < tamanio_lote ; i++){
                        fprintf (archivo, "%d %d\n", movimientos[i].importe, movimientos[i].tipo);
                    }

                    fclose(archivo);
                    printf("... Lote guadado.\n");

                }

            levanta_semaforo(id_semaforo);
        }

        espera_mcs = generaAleatorio(1000, 2500);
        usleep(espera_mcs*1000);
    }

    return 0;
}

