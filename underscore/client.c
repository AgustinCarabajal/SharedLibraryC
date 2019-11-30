
/* EXAMPLE */

#include <stdio.h>
#include "socket.h"

int main() {

    // int sock = _lsocket("4000");
    int sock = _connect("127.0.0.1", "8888");

    int enviar = 1;
	char message[1000];

	printf("Conectado al servidor. Bienvenido al sistema, ya puede enviar mensajes. Escriba 'exit' para salir\n");

	while(enviar){
		fgets(message, 1000, stdin);			// Lee una linea en el stdin (lo que escribimos en la consola) hasta encontrar un \n (y lo incluye) o llegar a 1000.
		if (!strcmp(message,"exit\n")) enviar = 0;			// Chequeo que el usuario no quiera salir
		if (enviar) send(sock, message, strlen(message) + 1, 0); 	// Solo envio si el usuario no quiere salir.
	}

    close(sock);

    return 0;
}