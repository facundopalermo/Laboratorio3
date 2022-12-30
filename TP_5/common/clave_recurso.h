#ifndef __CLAVE_COMPARTIDA_H
#define __CLAVE_COMPARTIDA_H

    #include <sys/ipc.h>
    #include <stdlib.h>
    #include <stdio.h>
    
    key_t crear_clave (char *archivo, int r_clave);

#endif
