#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void controlador (int);

int main()
{
	signal (SIGINT, controlador);
	while (1)
		pause ();

	return 0;
}

void controlador (int numeroSenhal)
{
	printf ("Pues no me salgo \n");
	printf ("Intentalo otra vez\n");
	signal (SIGINT, SIG_DFL);
}