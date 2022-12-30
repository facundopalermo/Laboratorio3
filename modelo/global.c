#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "./headers/global.h"


pthread_mutex_t mutex;

int numeroAleatorio (int desde, int hasta) {
    return rand() % (hasta - desde + 1) + desde;
}