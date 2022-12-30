#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define CLAVE_BASE 33 /* Esta puede ir en un *.h para que los programas lo usen */
#define CANTIDAD 10
#define CANTIDAD_TOTAL 10
#define DESDE 0
#define HASTA 25

typedef struct tipo_dato
{
    int numero;
    char letra;
}dato;


/**
 * @brief PASO 1 - Crear clave
 */
key_t crear_clave (int r_clave) {

    key_t clave = ftok("/bin/ls", r_clave);

    if ( clave == (key_t) -1 ) {
        printf("Error al crear la clave");
    }

    return clave;
}

/**
 * @brief PASO 2 - Crear zona de memoria
 * 
 * ! int shmget (key_t, int, int)
 * @param int (size) tamaño en bytes para la memoria
 * @param int (0777|IPC_CREAT) flags
 */
void * crear_memoria (int size, int * r_id_memoria, int clave_base) {

    void * ptr_memoria; 
    int id_memoria; /* identificador de memoria */

    id_memoria = shmget(crear_clave(clave_base), size, 0777|IPC_CREAT);

    if ( id_memoria == -1 ) {
        printf("No consigo id para memoria compartida\n");
        exit(0);
    }
    /**
     * @brief Atencion!
     * ! shmat () : shared memory attach operation
     * 
     * @param int id_memoria → la obtenida antes
     * @param char poner 0
     * @param int poner 0
     * 
     * ! IMPORTANTE: ( cast ) shmat ( ... )
     * *: cast .. ej: (mi_estructura) es el tipo de dato o estructura al que se desea apuntar la memoria compartida
     */
    ptr_memoria = (void *) shmat (id_memoria, (char*)0, 0);

    if ( ptr_memoria == NULL ){
        printf("No consigo memoria compartida\n");
        exit(0);
    }

    *r_id_memoria = id_memoria;
    return ptr_memoria; 
}

/**
 * @brief PASO 3 - LIBERAR MEMORIA
 * 
 * ! int shmdt (char *) : shared memory detach operation
 * desasocia la memoria
 * @param char ptr_memoria
 * 
 * ! int shmctl (int, int, struct shmid_ds) : Shared memory control operations
 * destruye la memora
 * @param int id_memoria
 * @param int IPC_RMID → indica que se quiere destruir
 * @param struct NULL
 * *Esta funcion solo la llama uno de los procesos.
 */

/**
 * @brief PASO 4 - Usar semaforos 
 */

int main(int argc, char const *argv[])
{
    int id_memoria;

    dato *memoria = NULL; //inicializar el puntero en NULL
    
    int i, aleatorio;

    memoria = (dato*)crear_memoria(sizeof(dato)*CANTIDAD, &id_memoria, CLAVE_BASE);

    srand(time(NULL));

    while (1) {

        printf ("Escrimos en la memoria");

        for( i=0; i < CANTIDAD; i++) {
            aleatorio = rand()%(HASTA-DESDE)+DESDE;

            memoria[i].numero = aleatorio;
            memoria[i].letra = 0x41 + aleatorio;

            printf("Escrito %d %c\n", memoria[i].numero, memoria[i].letra);
            sleep(1);
        }
        printf("Dejamos de escribir en la memoria\n");
        sleep(10);
    }

    //limpiar
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);

    return 0;
}
