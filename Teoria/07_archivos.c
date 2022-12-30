#include <stdio.h>
#include <stdlib.h>

/**
 * @brief FILE *fopen(char *nombre, char *modo) 
 * @param *modo w  :: write
 *              r  :: read
 *              a  :: append (agregar al final)
 *              w+ :: Lectura y escritura. No debe existir. Si existe, se elimina
 *              r+ :: Lectura y escritura. Si no existe, se crea vacio
 *              a+ :: Lectura y escritura al final. Si no existe, se crea vacio 
 */

int main () {

    char cadena[100];
    int numero;
    
    FILE *archivo; //puntero que apunta a FILE

    //siempre conviene validar si el puntero es NULL (que el archivo no existe)

    if( (archivo = fopen("archivo.txt", "w")) == NULL){
        printf("Error al abrir el archivo");
    } else {

     /**
     * @brief fprintf (FILE *fp, char *format, ...);
     * Para escrtibir en un archivo en un determinado formato.
     */

        fprintf(archivo, "%s %d\n", "Estoy guardando un uno: ", 1);

    }
    fclose(archivo); //para cerrar el archivo

    if( (archivo = fopen("archivo.txt", "r")) == NULL){
        printf("Error al abrir el archivo");
    } else {
    /**
     * @brief fscanf (FILE *fp, char *format, ..);
     * Para obtener los valores en un determinado formato y almacenarlo en los argumentos variables
     */

    /**
     * @brief int feof (FILE *stream);
     * indica si se ha llegado al final del archivo. retorna 0 si no se llegó al final del archivo.
     */

        while (!feof(archivo)){
            fscanf(archivo, "%s ", cadena);
            printf("%s ", cadena);
        }
    }
    fclose(archivo);    
    
}