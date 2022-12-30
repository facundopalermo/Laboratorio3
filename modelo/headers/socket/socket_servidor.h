#ifndef _SOCKET_SERVIDOR_H
#define _SOCKET_SERVIDOR_H

    int abre_socket_inet (char * servicio);
    int abre_socket_unix (char * servicio);
    int acepta_conexion_cliente (int descriptor);

#endif
