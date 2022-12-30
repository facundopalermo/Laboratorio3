#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define TIEMPO_INICIAL 2
#define TIEMPO_REPETICION 500
void tratamientoSenhal (int);


main()
{	
	struct itimerval contador; //estructura con el contador de tiempo

	struct timeval tiempoInicial; 

	struct timeval tiempoRepeticion;

	tiempoInicial.tv_sec=TIEMPO_INICIAL; //Tiempo inicial 2 segundos.
	tiempoInicial.tv_usec=0;

	tiempoRepeticion.tv_sec=0;
	tiempoRepeticion.tv_usec=TIEMPO_REPETICION*1000; //tiempo de repetici�n 500ms.

	contador.it_value=tiempoInicial;
	contador.it_interval=tiempoRepeticion;
	
	signal (SIGALRM, tratamientoSenhal);

	
	alarm(TIEMPO_INICIAL); //solo envia una se�al a los N segundos.
	
	//setitimer (ITIMER_REAL, &contador, NULL); //Nos permite enviar se�ales m�s definidas con inicio e intervalo.
	
	while(1)
		pause();
}

void tratamientoSenhal (int idSenhal)
{
	printf ("Recibida senial\n");
}