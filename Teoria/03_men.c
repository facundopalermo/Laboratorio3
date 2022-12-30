//memcmp(...); memcpy(...); memset(...);

#include <memory.h>
#include <stdio.h>
#include <string.h>

/**
 * ! → void *memcpy(void *dest, const void *src, size_t n);
 * @param dest puntero al array destino que contendrá la copia (casteado como void)
 * @param src puntero al orige de los datos a copiar
 * @param n cantidad de bytes a ser copiados
 * @return void* 
 
 * ! → int memcmp(const void *str1, const void *str2, size_t n)
 * @param str1 puntero al bloque de memoria 1
 * @param str2 puntero al bloque de memoria 2
 * @param n cantidad de bytes a comparar
 * @return int → if memcmp() < 0 then: str1 < str2
 *               if memcmp() > 0 then: str1 > str2
 *               if memcmp() = 0 then str1 == str2
 *
 * ! → void *memset(void *str, int c, size_t n)
 * @param str puntero al bloque de memoria a llenar
 * @param c valor a meter. Es int, pero la funcion llena el bloque utilizando la conversion de char para este valor.
 * @param n cantidad de bytes
 * @return puntero al area de memoria para str
 */



int main () {

    /**
     * ! Uso de memcpy()
     */
    printf("Uso de memcpy(): \n");
    const char src[50] = "Hola mundo";
    char dest [50];
    strcpy(dest, "Soy Facundo");
    //sprintf(dest, "Soy Facundo");
    printf("Antes de memcpy() dest = %s\n", dest);
    memcpy(dest, src, strlen(src)+1);
    printf("Despues de memcpy() dest = %s\n", dest);

    /**
     * ! Uso de memcmp()
     */
    printf("\nUso de memcmp(): \n");
    char str1[15];
    char str2[15];
    int resultado;

    memcpy(str1, "abcdef", 6);
    memcpy(str2, "ABCDEF", 6);


    resultado = memcmp(str1, str2, 5);

    if(resultado > 0) {
        printf("str1 > str2");
    } else if(resultado < 0) {
        printf("str1 < str2");
    } else {
        printf("str1 == str2");
    }    

    /**
     * ! Uso de memset()
     */
    printf("\nUso de memset(): \n");
    char str[50];

    strcpy(str,"Estas palabras se perderan y estas otras no");
    puts(str);

    memset(str,'#',26);
    puts(str);

    return 0;
}