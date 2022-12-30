#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main (){

	srand(time(NULL));
	printf("\nPID desde programa: %d\n", getpid());
	printf("Numero generado: %d\n", rand() % 100);
}
