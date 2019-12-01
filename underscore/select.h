#ifndef SELECT_LIB
#define SELECT_LIB

// STANDARD LIBRARIES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include "socket.h"

// DEFAULT VALUES

#define TRUE   1
#define FALSE  0
#define PORT 8888
#define MAX_CLIENTS 30

/**
 * METHOD: _select
 * 
 * Permite monitorear varias conexiones en un thread
 * 
 * @params: 
 *      lsocket -> Listener socket
 *      func -> Funcion custom a ejecutar en cada interaccion [use func(sd, buffer)]
 *          sd -> File Descriptor
 *          buffer -> Mensaje recibido de la conexion
 *      backlog -> Funcion custom a ejecutar en cada interaccion
 *
 * @example:
 *      Call with _lsocket("<SOME_PORT>");
 */
void _select(int lsocket, void (*func)(), int backlog);

#endif