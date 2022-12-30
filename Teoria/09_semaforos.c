#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h> // ** para la comunicacion entre PROCESOS

/** 
 * TODO 1) obtener clave del archivo
 * @brief  ftok() 
 * ! ftok ()
 * key_t ftok(char*, int)
 * @param char* es el pathname a un fichero
 * @param int 8 bits menos significativos de proj_id
 * *los procesos que trabajen con el mismo fichero deben tener el mismo int
 * 
 * @return key_t  → genera una clave IPC de System V de tipo key_t
 */


#include <sys/sem.h> // ** para semaforos

/**
 * TODO 2) obtener array de semaforo (crear semaforo)
 * @brief int semget(key_t, int, int)
 * ! semget ()
 * @param key_t se le debe pasar la clave obtenida con ftok
 * @param int cantidad de semaforos
 * @param int flags para permisos y modificadores de semafors
 * @return int → es un identificador del array de semaforo (0600 | IPC_CREATE)
 */

/**
 * TODO 3) iniciar semaforo
 * @brief int semctl(int, int, int, int)
 * ! semctl ()
 * @param int el identificador del array de semaforo
 * @param int → indice del semáforo a inicializar en el array. si solo se ha pedido un array, acá va 0
 * @param int → accion sobre que se quiere hacer. ej: SETVAL
 * @param int → 1 verde, 0 rojo
 * @return int 
 */

/**
 * TODO para operar y usar los semaforos
 * 
 * @brief int semop(int, struct sembuf *, size_t)
 * ! semop ()
 * @param int identificador de array
 * @param struct sembuf* → array de operaciones:
 *               operacion.sem_num = 0
 *               operacion.sem_op = 1      (1, -1)
 *               operacion.sem_flag = 0
 * @param size_t numero de elementos en el array → 1
 *  
 */

#define ROJO 0
#define VERDE 1
#define CLAVE_BASE 33

key_t creo_clave (int r_clave) {

    key_t clave;
    clave = ftok ("/bin/ls", r_clave);

    if ( clave == (key_t) -1 ) {
        printf ("No se pudo obtener clave para memoria compartida\n");
        exit(0);
    }

    return clave;
}

int creo_semaforo () {

    key_t clave = creo_clave(CLAVE_BASE);

    int id_semaforo = semget(clave, 1, 0600|IPC_CREAT);

    if ( id_semaforo == -1 ) {
        printf ("Error al crear el semaforo\n");
        exit(0);
    }

    return id_semaforo;
}

void inicia_semaforo (int id_semaforo, int valor) {
    semctl(id_semaforo, 0, SETVAL, valor);
}


void levanta_semaforo (int id_semaforo) {

    struct sembuf operacion;
    printf("Levanta SEMAFORO \n");

    operacion.sem_num = 0;
    operacion.sem_op = 1; //incrementa en 1
    operacion.sem_flg = 0;

    semop(id_semaforo, &operacion, 1);
}

void espera_semaforo (int id_semaforo) {

    struct sembuf operacion;
    printf("Espera SEMAFORO \n");

    operacion.sem_num = 0;
    operacion.sem_op = -1; //decrementa en 1
    operacion.sem_flg = 0;

    semop(id_semaforo, &operacion, 1);
}

int main () {
    int i;
    int id_semaforo;

    id_semaforo = creo_semaforo();

    inicia_semaforo(id_semaforo, VERDE);

    while(1){
        espera_semaforo(id_semaforo);
        printf("Seccion critica\n");
        sleep(1);
        levanta_semaforo(id_semaforo);
        sleep(10);
    }
    return 0;
}