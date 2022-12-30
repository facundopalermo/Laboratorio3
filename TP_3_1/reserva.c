#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

#define ROJO 0
#define VERDE 1
#define CLAVE_BASE 77
#define ARCHIVO_LOTE "lote.dat"
#define MIN_VUELO 1000
#define MAX_VUELO 1010
#define INTERVALO 300

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
void mostrar_reservas (Pasaje lote [], int n);
void backup_lote(Pasaje lote [], int n, int cont_archivo);


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
    semctl(id_semaforo, 0, SETVAL, valor);
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
void mostrar_reservas (Pasaje lote [], int n){
    int cont = 0;
    printf("VUELO\tDESTINO\tPASAJEROS\n");
    for (int vuelo = MIN_VUELO; vuelo <= MAX_VUELO; vuelo++) {
        for (int i = 0; i < n; i++){
            if (lote[i].vuelo == vuelo) {
                cont++;
            }
        }
        if (cont > 0) {
            printf("%d\t%s\t%d\n", vuelo, getDestino(vuelo), cont);
        }
        cont = 0;
    }
}

void backup_lote(Pasaje lote [], int n, int cont_archivo){

    FILE *nuevo_archivo;
    char nombre_archivo [13];
    sprintf(nombre_archivo,"lote.%03d.dat",cont_archivo);

    if( (nuevo_archivo = fopen (nombre_archivo, "w")) == NULL ) {
        printf("Error al hacer backup\n");
    } else {
        for (int i = 0; i < n ; i++){
            fprintf (nuevo_archivo, "%d %s %s\n", lote[i].vuelo, lote[i].destino, lote[i].nombre);
        }

        fclose(nuevo_archivo);
        printf("Datos guardados correctamente en %s\n\n", nombre_archivo);
    }
    
}

int main (void) {

    FILE *archivo_original;
    Pasaje lote [100]={0};
    int i = 0;

    int n_lote=0;

	int id_semaforo;
	id_semaforo =  crear_semaforo();
    
    printf("Esperando lotes...\n");
    while (1) {

        espera_semaforo(id_semaforo);

            if( (archivo_original = fopen (ARCHIVO_LOTE, "r")) == NULL ) {
                //printf("Error: no se pudo abrir lote.dat\n");
                printf("");
            } else {
                while (!feof(archivo_original)){
                    fscanf(archivo_original, "%d %s %s\n", &lote[i].vuelo, lote[i].destino, lote[i].nombre);
                    i++;
                }
                fclose(archivo_original);
                if (i > 0){
                    mostrar_reservas(lote, i);
                    backup_lote(lote, i, n_lote);
                }
                remove(ARCHIVO_LOTE);
                i = 0;
                n_lote++;
                memset(lote, 0, 100);
                printf("Esperando lotes...\n");
            }
        levanta_semaforo(id_semaforo);
        usleep(INTERVALO*1000); //300ms
    }
}