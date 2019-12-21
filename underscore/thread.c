#include "thread.h"

void _thread(char *port, void (*func)()) {
    int client;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    
    int lsocket = _lsocket(port);

    // Try to specify maximum of n pending connections for the master socket
    if (listen(lsocket, BACKLOG) < 0) {
        perror("[UScore Lib Error] -listen");
        exit(EXIT_FAILURE);
    }
    puts("[UScore Lib Info]: Waiting for connections ...");
	
	while ((client = accept(lsocket, (struct sockaddr *) &addr, &addrlen))) {

        data = malloc(sizeof(_cdata));
		data -> client = client;
		data -> server = lsocket;
		pthread_create(&_tcon, NULL, (void *)func, (void*)data);
		
	}

	pthread_join(_tcon, NULL);
}
