#include <stdio.h>
#include <stdlib.h>

/*
    Mecanismos de Comunicacion entre procesos (IPC):
        ♦ Archivos
        ♦ Memoria compartida
        ♦ Cola de mensajes
    
    Recursos de comunicacion entre procesos (IPC)
        ♣ Semaforos
        ♣ Cola de mensajes
        ♣ Memoria compartida

*/

/**
 * @brief Sección crítica
 * 
 * Entrada en la seccion critica → Codigo de la seccion critica → Salida de la sección critica
 * 
 * Require:
 *          ♦ Exclusion mutua: si un ps está ejecutando la SC, ningun otro puede hacerlo
 *          ♦ Progreso: de acuerdo a los procesos que quieren entrar a la SC, se decide.
 *          ♦ Espera acotada: debe haber un limite en el numero de veces que los demas PS entran antes de que entre el que solicita
 */

#include <sys/ipc.h> // ** para la comunicacion entre PROCESOS
/** 
 * @brief  ftok() 
 * ! ftok()
 * key_t ftok(char*, int)
 * @param char* es el pathname a un fichero
 * @param int 8 bits menos significativos de proj_id
 * @return key_t  → genera una clave IPC de System V de tipo key_t
 * 
 * TODO: usar con
 *                  msgget () → cola de mensajes
 *                  semget () → semaforo
 *                  shmget () → memoria compartida
 */

#include <sys/msg.h> // ** cola de MENSAJES
/**
 *      msgctl ()
 *      msgget ()
 *      msgrcv ()
 *      msgsnd ()
 */

#include <sys/shm.h> // ** MEMORIA compartida
/**
 *      shmat ()
 *      shmctl ()
 *      shmdt ()
 *      shmget ()
 */

#include <sys/sem.h> // ** SEMAFOROS
/**
 *      semctl ()
 *      semget ()
 *      semop ()
 */

// ! Ejemplo */

key_t creo_clave () {

    key_t clave;
    clave = ftok ("/bin/ls", 33);

    if ( clave == (key_t)-1 ) {
        printf ("No puedo conseguir clave semaforo, mem compartida, etc.\n");
        exit(0);
    }

    return clave;

}

int main () {
    printf("%d\n", creo_clave);
}
 