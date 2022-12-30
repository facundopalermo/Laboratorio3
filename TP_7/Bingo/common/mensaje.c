#include "../headers/mensaje.h"

int crear_cola_mensaje(char *archivo_clave, int clave_base) {
    int id_cola_mensaje;
    id_cola_mensaje = msgget(crear_clave(archivo_clave, clave_base), 0777|IPC_CREAT);
    if (id_cola_mensaje == -1){
        printf("Error al crear la cola de mensajes\n");
        exit(EXIT_FAILURE);
    }

    return id_cola_mensaje;
}

int enviar_mensaje(int id_cola_msg, long destino, int remitente, int evento, char* cuerpo) {

    Mensaje mensaje;
    int snd;

    mensaje.destinatario = destino;
    mensaje.remitente = remitente;
    mensaje.evento = evento;
    strcpy(mensaje.cuerpo, cuerpo);
    snd = msgsnd(id_cola_msg, (struct msgbuf *) &mensaje, sizeof(mensaje.remitente)+sizeof(mensaje.evento)+sizeof(mensaje.cuerpo), IPC_NOWAIT);
    return snd;
}

int recibir_mensaje(int id_cola_msg, long destino, Mensaje *entrada) {

    Mensaje mensaje;
    int res;

    res = msgrcv(id_cola_msg, (struct msgbuf*)&mensaje, sizeof(mensaje.remitente)+sizeof(mensaje.evento)+sizeof(mensaje.cuerpo), destino, 0);
    entrada->destinatario = mensaje.destinatario;
    entrada->remitente = mensaje.remitente;
    entrada->evento = mensaje.evento;
    strcpy(entrada->cuerpo, mensaje.cuerpo);
    return res;
}

int borrar_mensajes(int id_cola_msg) {
	Mensaje mensaje;
	int res;
	do
	{
		res = msgrcv (id_cola_msg, (struct msgbuf *)&mensaje,  sizeof(mensaje.remitente)+sizeof(mensaje.evento)+sizeof(mensaje.cuerpo),	0, IPC_NOWAIT);
	}while(res > 0);

	return res;
}

void liberar_cola_mensajes(int id_cola_mensajes) {
    msgctl(id_cola_mensajes, IPC_RMID, (struct msqid_ds*) NULL);
}