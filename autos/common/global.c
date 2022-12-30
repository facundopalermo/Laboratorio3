#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


pthread_mutex_t mutex;


/*los utilizo en las dos */
int aleatorio(int desde, int hasta){
    return rand()%(hasta - desde+1)+desde;
}
