#include <stdio.h>
#include <stdlib.h>

typedef struct dato{
	int num1;
	int num2;
} datos;

void intercabiar(datos *numeros){
	int aux;
	datos auxNumeros = *numeros;
	aux = auxNumeros.num1;
	auxNumeros.num1 = auxNumeros.num2;
	auxNumeros.num2 = aux;
	
	printf("%d, %d\n", auxNumeros.num1, auxNumeros.num2);
	
	//*numeros = auxNumeros;
	
}

int main (){
	datos numeros;
	
	numeros.num1 = 10;
	numeros.num2 = 20;
		
	intercabiar(&numeros);
		
	printf("%d, %d\n", numeros.num1, numeros.num2)
	
	return 0	
}