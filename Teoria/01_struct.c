#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARTAS 48 //constantes

struct carta{
	int numero;
	char palo[7];
};

typedef struct carta Carta;
//es una redefinicion de un struct
//acá cambia carta por Carta

typedef char Palo[7];

void inicializar_mazo(Carta m[], Palo p[]);
void barajar(Carta m[]);
void imprimir(Carta m[]);

int main(){
	int i;
	Carta mazo[CARTAS];
	//struct carta mazo[CARTAS];
	
	/*
		mazo[0].numero = 1
		strcpy(mazo[0].palo, "copa");
		o
		sprintf(mazo[0].palo, "copa");
	*/
	
	Palo p[4] = {"copa", "oro", "espada", "basto"};
	srand(time(NULL)); 
	
	inicializar_mazo(mazo, p);
	barajar(mazo);
	imprimir(mazo);
	system("PAUSE");
	return 0;
}