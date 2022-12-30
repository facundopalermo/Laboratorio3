/* hilo: unidad basica de utiizacion del procesador:

        * ID de hilo
        * cntador de programa
        * conjunto de registros
        * una pila
    
    -------------------------------
    | CODIGO     DATOS   ARCHIVOS |
    |------------------------------
    |registros|registros|registros| 
    |  pila   |  pila   |   pila  |
    |------------------------------
    |         |         |         |
    |    h    |    h    |    h    |
    |    i    |    i    |    i    |
    |    l    |    l    |    l    |
    |    o    |    o    |    o    |
    |         |         |         |
    -------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define CANTIDAD 10

//variable global para semaforo (mutex)
pthread_mutex_t mutex;

void *funcionThread (void *parametro) {
    //logica o tarea del hilo
    int i;
    printf("hijo\n");

    for(i=0; i<CANTIDAD; i++) {
        pthread_mutex_lock(&mutex);
            printf("Soy el hijo y tengo el mutex\n");
            sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    printf("Soy el hijo y espero 10 seg\n");
    sleep(10);
    printf("Hijo : termino\n");
    pthread_exit((void*)"Listo");
}

int main(int argc, char const *argv[]) {
    pthread_t id_hilo;
    pthread_attr_t atributos;
    int error;
    int i;
    char * valorDevuelto = NULL;

    //inicia semaforo (mutex)
    pthread_mutex_init(&mutex, NULL);

    //inicializa los atributos del hilo
    pthread_attr_init(&atributos);

    /**
     * @brief setear estado inicial del hijo
     * @param PTHREAD_CREATE_JOINABLE indica que voy a esperar la finalizacion del hilo. habilita pthread_join()
     */
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    /**
     * @brief lanzamos el hilo
     * 
     * @param id_hilo se carga cuando se crea
     * @param atributos los atributos del hilo
     * @param funcionThread funcion a ejecutar
     * @param NULL iría la direccion de memoria que recibe como parametro la funcion del hilo (void *parametro)
     * 
     */
    if ( pthread_create (&id_hilo, &atributos, funcionThread, NULL) != 0) {
        perror("no puedo crear thread");
        exit(-1);
    }

    for(i=0; i<CANTIDAD; i++){
        pthread_mutex_lock(&mutex);
            printf("Soy el padre y tengo el mutex\n");
            sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    printf("Padre: Espero al thread\n");

    //pthread_join es una funcion bloqueante que evita que finaice main, y espera a los hilos
    pthread_join(id_hilo, (void**)&valorDevuelto);
    printf("Padre: ya ha terminado el thread\n");
    printf("Padre: devuelve \"%s\"\n", valorDevuelto);

    return 0;
}


