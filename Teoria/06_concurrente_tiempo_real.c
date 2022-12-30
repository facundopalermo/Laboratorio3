#include <sys/types.h>
#include <unistd.h>

// Primitivas POSIX ID proceso

pid_t getpid (void); //ID proceso
pid_t getppid (void); //ID proceso padre

// uid_t getuid (void); //ID usuario
// uid_t geteuid (void); //ID usuario efectivo

/*
    fork () → crea una nueva copia exacta del proceso y ambos continuan a partir de allí desde donde se quedó antes de fork().

*/

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
#include <pthread.h>

    int phtread_create (pthread_t *thread,
                        const pthread_attr_t *attr,
                        void *(*start_routine) (void *),
                        void *arg);
    
    int pthread_join (pthread_t thread, void **reval);

/*
    $ gcc -lpthread thread_simple.c -o thread_simple
    $ ./thread_simple <valor>

    ver codigo ejemplo apunte 3. Programacion Concurrente y Tiempo Real (Capitulo 1.pdf), pagina 9
*/