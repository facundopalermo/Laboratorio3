#include <stdio.h>
#include <stdlib.h>

#define ARCHIVO "producto.txt"
#define CANT_POR_LOTE 10

void producir (int cantidad);
void consumir (int cantidad);

int main ( void ) {

	printf("Producir productos:\t");
	producir(CANT_POR_LOTE);

	printf("\nConsumir un poco:\n");
	consumir(5);
	
	printf("\n***********************************************************\n");

	/* No tiene sentido volver a llamar la funcion, 
	ya que para el ejemplo, consumir no borra las lineas,
	porque se usa el modo "r" que es solo para leer.

	Pero a fines de ejemplo, vuelvo a llamar a la funcion, que por usar "w", 
	reescribirà los 10 productos.*/

	printf("\nProducir productos:\t");
	producir(CANT_POR_LOTE);
	printf("\nQuerer consumir mas de lo que hay:\n");
	consumir(15);
}

void producir (int cantidad) {

	FILE *almacen;

	if ( (almacen = fopen(ARCHIVO, "w")) == NULL ){
		printf( "Error al abrir el archivo" );
	} else {
		
		for (int i = 1; i <= cantidad; i++ ){
			fprintf (almacen, "PRODUCTO-%02d\n", i);
		}
		
		fclose (almacen);
		printf("%d productos producidos\n", cantidad);
	}
}

void consumir (int cantidad) {
	
	FILE *almacen;
	char producto[30];
	int cont = 0;
	
	if( (almacen = fopen(ARCHIVO, "r")) == NULL ){
		printf("Error al procesar el archivo");
	} else {
		
		/* hago uso de EOF en vez de feof(almacen). porque al usar feof y el contador,
		 se lee la linea vacia del \n del producto 10
		Entonces me duplica esa linea.*/
	
		while (((fscanf(almacen, "%s", producto)) != EOF) && (cont < cantidad) ){
			printf("%s consumido\n", producto);
			cont++;
		}

		fclose(almacen);
		printf("\nSe consumieron %d productos de los %d solicitados ", cont, cantidad);
		if (cont< cantidad)
			printf("(no hay mas productos)");
		printf("\n");
	}
}

/*
Pregunta 3)
El comportamiento es claro. Al "producir" se crea el archivo o se escribe el existente
(siempre que el programa tenga acceso para hacerlo).
Luego al "consumir" se lee linea a linea hasta el final del archivo.

Pregunta 4)
Para que sea una simulacion de la realidad, se deberìa producir y consumir a la vez.
Supongo que la falla estarìa enla concurrencia sobre el archivo, ya que a medida
a medida que se quiere producir, se tendria que poder consumir. Ademas supongo que no serìa
solo un cliente el que quiere un auto, entonces se tendria que estar validando si ese auto 
aun se puede consumir o no y que opciones nuevas estan para consumo. Estimo que seran temas
a ver en futuros modulos.
*/
