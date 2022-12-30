/* Todas las señales pueden ser ignoradas o bloqueadas
con excepcion de 
    ! SIGSTOP
    ! SIGKILL

las señales seran tratadas en cualquier orden.

* pause ()  → pausa el proceso o thread en espera de una señal. retorna -1 cuando la funcion de tratamiento de señal termina.
*/

/**
 * signal (int __sig, sig_t funcion) → para dar tratamiento a una señal *
 * @param __sig la señal que se espera recibir.
 * @param funcion puntero a una funcion.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void manejador(int signum);

int con = 0;

int main(int argc, char const *argv[])
{
    signal(SIGINT, manejador);

    printf("Ejemplo de signal\n");

    while(con <= 5) ;

    return 0;
}

void manejador (int signum) {
    printf("recibí la señal sigint\n");
    con++;
    signal(SIGINT, manejador);
}
