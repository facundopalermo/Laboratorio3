#ifndef __GLOBAL_PORUNACABEZA_H
#define __GLOBAL_PORUNACABEZA_H

    #include <sys/types.h>
    
    #define CLAVE_BASE 33
    #define ARCHIVO_BASE "/bin/ls"

    typedef enum {
        MSG_NADIE,
        MSG_HIPODROMO,
        MSG_CABALLO
    } Destinos;

    typedef enum {
        EVT_NINGUNO,
        EVT_INICIO,
        EVT_METROS,
        EVT_SIGA,
        EVT_CRUZARON_EL_DISCO
    } Eventos;

    int numeroAleatorio (int desde, int hasta);
    int validar_caballos (int argc, char const *argv[]);

#endif
