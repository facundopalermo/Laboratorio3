#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/socket/socket.h"

int lee_socket (int fd, char * datos, int longitud) {
	int leido = 0;
	int aux = 0;

	if ((fd == -1) || (datos == NULL) || (longitud < 1)){
		return -1;
	}

	/* Mientras no hayamos leido todos los datos solicitados */
	while (leido < longitud)
	{
		aux = read(fd, datos + leido, longitud - leido);
		if (aux > 0){
			leido = leido + aux;
		} else {

			if (aux == 0) {
				return leido;
			}

			if (aux == -1) {
				switch (errno) {
					case EINTR:
					case EAGAIN:
						usleep(100);
						break;
					default:
						return -1;
				}
			}
		}
	}

	return leido;
}

int escribe_socket(int fd, char * datos, int longitud) {
	int escrito = 0;
	int aux = 0;

	if ((fd == -1) || (datos == NULL) || (longitud < 1))
		return -1;

	while (escrito < longitud) {
		aux = write(fd, datos + escrito, longitud - escrito);
		if (aux > 0) {
			escrito = escrito + aux;
		} else {
			if (aux == 0) {
				return escrito;
			} else {
				return -1;
			}
		}
	}

	return escrito;
}
