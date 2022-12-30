#include "./headers/global.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*los utilizo en las dos */
int aleatorio(int desde, int hasta){
    return rand()%(hasta - desde+1)+desde;
}
