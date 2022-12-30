#ifndef __SEMAFORO_H
#define __SEMAFORO_H
    int crear_semaforo (char *archivo_base, int r_clave);
    void iniciar_semaforo (int id_semaforo, int color);
    void espera_semaforo (int id_semaforo);
    void levanta_semaforo (int id_semaforo);
#endif