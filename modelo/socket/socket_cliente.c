#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include "../headers/socket/socket_cliente.h"

int abre_conexion_unix (char * servicio) {
	struct sockaddr_un direccion;
	int descriptor;

	strcpy (direccion.sun_path, servicio);
	direccion.sun_family = AF_UNIX;

	descriptor = socket (AF_UNIX, SOCK_STREAM, 0);
	if (descriptor == -1) {
		return -1;
	}

	if (connect (descriptor, 
			(struct sockaddr *)&direccion, 
			strlen (direccion.sun_path) + sizeof (direccion.sun_family)) == -1) {
		return -1;
	} else {
		return descriptor;
	}
}

int Abre_Conexion_Inet (char * host_servidor, char * servicio) {
	struct sockaddr_in direccion;
	struct servent * puerto;
	struct hostent * host;
	int descriptor;

	puerto = getservbyname (servicio, "tcp");
	if (puerto == NULL) {
		return -1;
	}
		

	host = gethostbyname (host_servidor);
	if (host == NULL) {
		return -1;
	}

	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = ((struct in_addr *)(host->h_addr))->s_addr;
	direccion.sin_port = puerto->s_port;
	
	descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (descriptor == -1){
		return -1;
	}
		
	if (connect (descriptor, 
			(struct sockaddr *)&direccion, 
			sizeof (direccion)) == -1) {
		return -1;
	}

	return descriptor;
}
