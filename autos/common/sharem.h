#ifndef __SH_H
#define __SH_H

    void *creo_memoria(int size, int *r_id_memoria, int clave_base);
    void liberar_memoria(void *memoria, int id_memoria);

#endif