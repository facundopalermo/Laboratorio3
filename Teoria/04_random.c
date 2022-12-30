#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){

    /**
     * int numero = rand() % (N-M+1) + M;   numero entero entre M y N
     * rand genera la misma secuencia de numeros aleatorios ya que la semilla que usa es siempre la misma
     * 
     * para generar aleatorios de verdad usar srand(semilla)
     * 
     * srand(parametro) : y se debe usar un numero diferente en cada ejecucion
     *      time(NULL)
     *      
     */

    //inicializo la semilla para aleatorios diferentes con cada ejecución
    srand(time(NULL));

    printf("%d", rand() % 11 );
    return 0;
}