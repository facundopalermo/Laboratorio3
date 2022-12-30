#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int main (){
    pid_t child;

    if ((child = fork()) == -1) { //fork retorna -1 al proceso padre, si fracasa y no crea hijos.
        perror("fork");
        exit (EXIT_FAILURE);
    } else if(child == 0) {
        puts ("En el proceso hijo");
        printf("\tpid = %d\n", getpid());
        printf("\tppid = %d\n", getppid());

        exit(EXIT_SUCCESS);
    } else {
        puts("En el proceso padre");
        printf("\tpid = %d\n", getpid);
        printf("\tppid = %d\n", getppid());
    }

    exit(EXIT_SUCCESS);
}

//exite vfork que no copia todo, es mas rapido.
