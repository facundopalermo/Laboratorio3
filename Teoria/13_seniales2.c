/**
 * @brief int kill (pid_t id, int sig)
 * @param id de proceso
 * @param sig señal
 */

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void manejador (int signum);

int bandera = 1;

int main(int argc, char const *argv[])
{
    int status, pid;

    if ((pid = fork()) == 0) {
        printf("Soy hijo y estoy esperando una señal de mi padre, mi pid es: %d\n", getpid());

        signal(SIGUSR1, manejador);
        while(bandera)
            ;

        kill(getppid(), SIGUSR2);
    } else {
        signal(SIGUSR2, manejador);
        printf("Soy padre, mi pid es: %d\n", getpid());
        sleep(3);

        kill(pid, SIGUSR1);
        wait(&status);
        printf("Mi hijo terminó con un estado: %d\n", status);
    }
    return 0;
}

void manejador(int signum) {
    if(signum == SIGUSR1) {
        printf("Recibí una señal de mi padre %d\n", signum);
    } else {
        printf("Recibí una señal de mi hijo %d\n", signum);
    }
    bandera = 0;
}
