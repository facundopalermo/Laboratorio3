#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define CLAVE_BASE 77
#define MAX_CAJEROS 3
#define INTERVALO 500
#define VERDE 1
#define ROJO 0

typedef struct movimiento{
    int importe;
    int tipo; // 0 cheque | 1 efectivo
} Movimiento;

typedef struct registro {
    int n_efectivo; //n: cantidad
    int m_efectivo; //m: monto total
    int n_cheque;
    int m_cheque;
}Registro;

typedef struct cajero {
    int num;
    Registro registro;
    int lote;
}Cajero;

key_t crear_clave (int r_clave);
int crear_semaforo ();
void iniciar_semaforo (int id_semaforo, int valor);
void levanta_semaforo (int id_semaforo);
void espera_semaforo (int id_semaforo);
void procesarLote (Cajero *cajero );
void backup_lote(Movimiento movimientos[], int cajero, int n, int cont_archivo);
void procesarTotal(Registro *total, Cajero cajeros[]);
void mostrarResumen(Registro r, Cajero cajeros[]);

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

//FUNCIONES ESPECIFICAS

void procesarLote (Cajero *cajero ) {

    FILE *archivo_original;
    Movimiento movimientos [999];

    char nombre_archivo[12];
    int i = 0;

    sprintf(nombre_archivo,"cajero%d.dat", cajero->num);

    if( (archivo_original = fopen (nombre_archivo, "r")) == NULL ) {
        //printf("Error: no se pudo abrir lote.dat\n");
        printf("");
    } else {
        while (!feof(archivo_original)){
            fscanf(archivo_original, "%d %d\n", &movimientos[i].importe, &movimientos[i].tipo);
            i++;
        }
        fclose(archivo_original);

        if ( i > 0){
            backup_lote(movimientos, cajero->num, i, cajero->lote);
            cajero->lote ++;

            for (int j = 0; j < i; j++) {
                if(movimientos[j].tipo == 0){
                    cajero->registro.m_cheque += movimientos[j].importe;
                    cajero->registro.n_cheque++;

                } else if (movimientos[j].tipo == 1){
                    cajero->registro.m_efectivo += movimientos[j].importe;;
                    cajero->registro.n_efectivo++;
                }
            }

        }
        remove(nombre_archivo);
        i = 0;
        memset(movimientos, 0, 20);
    }
}

void backup_lote(Movimiento movimientos[], int cajero, int n, int cont_archivo){

    FILE *nuevo_archivo;
    char nombre_archivo [16];
    sprintf(nombre_archivo,"cajero%d.%03d.dat", cajero, cont_archivo);

    if( (nuevo_archivo = fopen (nombre_archivo, "w")) == NULL ) {
        printf("Error al hacer backup\n");
    } else {
        for (int i = 0; i < n ; i++){
            fprintf (nuevo_archivo, "%d %d\n", movimientos[i].importe, movimientos[i].tipo);
        }

        fclose(nuevo_archivo);
        printf("Datos guardados correctamente en %s\n\n", nombre_archivo);
    }
    
}

void procesarTotal(Registro *total, Cajero cajeros[]){

    int cant_cheques = 0;
    int total_cheques = 0;
    int cant_efectivo = 0;
    int total_efectivo = 0;

    for (int i = 0; i < MAX_CAJEROS; i++) {

        cant_cheques += cajeros[i].registro.n_cheque;
        cant_efectivo += cajeros[i].registro.n_efectivo;
        total_cheques += cajeros[i].registro.m_cheque;
        total_efectivo += cajeros[i].registro.m_efectivo;

    }

    total->n_cheque = cant_cheques;
    total->m_cheque = total_cheques;
    total->n_efectivo = cant_efectivo;
    total->m_efectivo = total_efectivo;

}

void mostrarResumen(Registro r, Cajero cajeros[]){
    
    char cabecera[100];
    sprintf(cabecera,"TC-EFEC\t\tT$-EFEC\t\tTC-CHEQ\t\tT$-CHEQ\n");

    system("clear");
    printf("TOTAL:\n");
    printf("%s", cabecera);
    printf("%d\t\t$%d\t\t%d\t\t$%d\n", r.n_efectivo, r.m_efectivo, r.n_cheque, r.m_cheque);
    printf("\n");

    for (int i = 0; i < MAX_CAJEROS; i++) {

        printf("CAJERO%d:\n", i+1);
        printf("%s", cabecera);
        printf("%d\t\t$%d\t\t%d\t\t$%d\n", cajeros[i].registro.n_efectivo, cajeros[i].registro.m_efectivo, cajeros[i].registro.n_cheque, cajeros[i].registro.m_cheque);
        printf("\n");

    }

    printf("Esperando lotes para actualizar...\n");
    
}

int main ( void ) {

    int id_semaforo = crear_semaforo();
    Registro total;
    Cajero cajeros[MAX_CAJEROS];

    //inicializo registros
    for(int i = 0; i < MAX_CAJEROS; i++){
        cajeros[i].num = i+1;
        cajeros[i].lote = 0;
        cajeros[i].registro.m_cheque = 0;
        cajeros[i].registro.m_efectivo = 0;
        cajeros[i].registro.n_cheque = 0;
        cajeros[i].registro.n_efectivo = 0;
    }
    
    while (1) {

        espera_semaforo(id_semaforo);

            for(int i = 0; i < MAX_CAJEROS; i++){

                procesarLote(&cajeros[i]);

            }

        levanta_semaforo(id_semaforo);

        /*
        coloco acá el proceso del total y resumen porque 
        no me parece correcto mantener bloqueado el archivo 
        mientras se procesas las structuras en memoria
        El ejercicio dice "Al finalizar cada lote", la interpretacion
        creo que es valida. 
        */
        procesarTotal(&total, cajeros);
        mostrarResumen(total, cajeros);

        usleep(INTERVALO*1000); //500ms
    }

}