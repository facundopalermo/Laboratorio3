#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * @brief sys/wait
 * pid_t wait(int *status);
 * pid_t waitpid(pid_t pid, int *status, int options);
 * 
 * @param status almacena condicion de salida del proceso hijo
 * @param pid es la PID del proceso pos el cual se espera:
 *         < -1 → aguarda por cualquier proceso hijo cuya PGID sea igual al valor absuloto del PID
 *          -1 → Espera cualquier proceso
 *           0 → Aguarda por cualqueir proceso cuya PGID sea igual a la del proceso que efecuó la llamada
 *         > 0 → Espera por el proceso hijo cuya PID sea igual a pid 
 * 
 * @param options comportamiento: WNOHANG - WUNTRACED - WUNTRACED
 * 
 */

int main (){
    pid_t hijo;
    int condicion;

    if((hijo = fork()) == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    } else if(hijo == 0) {
        puts("En proceso hijo:");
        printf("\tpid de proceso hijo = %d/n", getpid());
        printf(stdout, "\tppid de proceso hijo = %d\n", getppid());
        exit(EXIT_SUCCESS)
    } else {
        waitpid(hijo, &condicion, 0);
        puts("En proceso padre:");
        printf("\tpid de proceso padre = %d/n", getpid());
        printf("\tppid de proceso padre = %d\n", getppid());
        printf("\tEl proceso hijo retorno %d\n", condicion);
    }
    exit (EXIT_SUCCESS);
}
