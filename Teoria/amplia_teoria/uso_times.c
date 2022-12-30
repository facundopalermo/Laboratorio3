#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/times.h>
#include <time.h>

void calcular_segundos (char *, clock_t);

int main (){
    clock_t comienzo, fnal, tics_insumidos;
    struct tms tic_comienzo, tic_final;

    comienzo = times(&tic_comienzo);

    system("grep el /usr/doc/*/* > /dev/null 2> /dev/null");

    final = times (&tic_final);
    tics_insumidos = final - comienzo;

    calcular_segundos("Tiempo transcurrido", tics_insumidos);

    puts("Tiempos de proceso padre");
    calcular_segundos ("\tuso de CPU por usuario", tic_final.tms_utime);
    calcular_segundos ("\tuso de CPU por sistema", tic_final.tms_stime);

    puts("Tiempos de proceso hijo");
    calcular_segundos ("\tuso de CPU por usuario", tic_final.tms_cutime);
    calcular_segundos ("\tuso de CPU por sistema", tic_final.tms_cstime);

    exit(EXIT_SUCCESS);
}

void calcular_segundos (char *cadena, clock_t tics_insumidos){
    long tics_por_seg = sysconf(_SC_CLK_TCK); //requerida para pasar los tics a segundos...

    printf("%s: %6.2f segundos\n", cadena, (float) tics_insumidos/tics_por_seg);
}