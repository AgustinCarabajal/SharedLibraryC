#include "socket.h"

int _lsocket(char *port) {

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // No importa si uso IPv4 o IPv6
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
	int opt = 1;

    if (getaddrinfo(NULL, port, &hints, &serverInfo) < 0)
    {
        perror("[UScore Lib Error]");
        exit(EXIT_FAILURE);
    }

    int list_sock = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

    bind(list_sock, serverInfo->ai_addr, serverInfo->ai_addrlen);
    freeaddrinfo(serverInfo);

	// set socket to allow multiple connections
    if(setsockopt(list_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        perror("[UScore Lib Error] -setsockopt");
        exit(EXIT_FAILURE);
    }

	printf("Listener on port %s \n", port);

    return list_sock;
}

int _connect(char *ip, char *port){

	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(ip, port, &hints, &serverInfo);

	int socketServer = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	if(socketServer < 0) {
		perror("[UScore Lib Error]");
		exit(EXIT_FAILURE);
	}

	int conexion = connect(socketServer, serverInfo->ai_addr, serverInfo->ai_addrlen);

	if(conexion < 0) {
		perror("[UScore Lib Error]");
		exit(EXIT_FAILURE);
	}

	fprintf (stdout, "\n-------------------------\n\n");
  	fprintf (stdout, "Status: \tSuccess\n");
  	fprintf (stdout, "Port: \t\t%s\n\n", port);
  	fprintf (stdout, "-------------------------\n\n");

	freeaddrinfo(serverInfo);

	return socketServer;
}

int _listen(int socket, int backlog) {
    
    listen(socket, backlog);

	struct sockaddr_in addr;           // Esta estructura contendra los datos de la conexion del cliente. IP, puerto, etc.
	socklen_t addrlen = sizeof(addr);

	int socketCliente = accept(socket, (struct sockaddr *) &addr, &addrlen);

    return socketCliente;
}

int _dlisten(int socket) {
    
    listen(socket, _BACKLOG);

	struct sockaddr_in addr;           // Esta estructura contendra los datos de la conexion del cliente. IP, puerto, etc.
	socklen_t addrlen = sizeof(addr);

	int socketCliente = accept(socket, (struct sockaddr *) &addr, &addrlen);

    return socketCliente;
}