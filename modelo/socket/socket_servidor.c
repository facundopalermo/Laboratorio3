#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#include "../headers/socket/socket_servidor.h"

int abre_socket_unix (char * servicio) {
	struct sockaddr_un direccion;
	int descriptor;

	descriptor = socket(AF_UNIX, SOCK_STREAM, 0);
	if (descriptor == -1){
		return -1;
	}

	strcpy(direccion.sun_path, servicio);
	direccion.sun_family = AF_UNIX;

	/*
	 * le da nombre al socket para que el cliente pueda conectarse.
	*/
	if (bind(descriptor, 
			(struct sockaddr *) &direccion,
			strlen(direccion.sun_path) + sizeof(direccion.sun_family)) == -1) {

		close(descriptor);
		return -1;
	}

	if (listen(descriptor, 1) == -1)
	{
		close(descriptor);
		return -1;
	}

	return descriptor;
}

int acepta_conexion_cliente(int descriptor) {
	socklen_t longitud_cliente;
	struct sockaddr cliente;
	int hijo;

	longitud_cliente = sizeof(cliente);
	hijo = accept(descriptor, &cliente, &longitud_cliente);
	if (hijo == -1){
		return -1;
	}
	return hijo;
}

int abre_socket_inet(char * servicio) {
	struct sockaddr_in direccion;
	struct sockaddr cliente;
	socklen_t longitud_cliente;
	struct servent * puerto;
	int descriptor;

	descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (descriptor == -1) {
		return -1;
	}

	puerto = getservbyname(servicio, "tcp");
	if (puerto == NULL){
		return -1;
	}

	direccion.sin_family = AF_INET;
	direccion.sin_port = puerto->s_port;
	direccion.sin_addr.s_addr = INADDR_ANY;

	if (bind(descriptor,
			(struct sockaddr *)&direccion,
			sizeof(direccion)) == -1) {
		close(descriptor);
		return -1;
	}

	if (listen(descriptor, 1) == -1) {
		close(descriptor);
		return -1;
	}

	return descriptor;
}
