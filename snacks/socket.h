#ifndef SOCKET_LIB
#define SOCKET_LIB

// STANDARD LIBRARIES

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

// DEFAULT VALUES

#define SNACK_PORT "4000"       // Puerto por defecto
#define SNACK_BACKLOG 3			// Define cuantas conexiones vamos a mantener pendientes al mismo tiempo
#define SNACK_PACKAGESIZE 1024	// Define cual va a ser el size maximo del paquete a enviar

struct addrinfo hints;
struct addrinfo *serverInfo;

/**
 * METHOD: snack_socket
 * 
 * Crea un socket listenner para un puerto dado
 * 
 * @params: 
 *      port -> Puerto donde escuchar las conexiones 
 * 
 * @return: Devuelve un socket listenner
 */

int snack_socket(char* port);

/**
 * METHOD: snack_connect
 * 
 * Crea una conexion para una ip y un puerto especificos
 * 
 * @params: 
 *      ip   -> Ip destino para la conexion
 *      port -> Puerto destino para la conexion
 *  
 * @return: Devuelve el socket de la conexion
 */

int snack_connect(char *ip, char *port);

/**
 * METHOD: snack_listen
 * 
 * Espera una conexion y devuelve un socket con la informacion de la misma
 * 
 * @params: 
 *      socket   -> Listener socket
 *      backlog  -> Cantidad de conexiones simultaneas
 *  
 * @return: Devuelve el socket de la conexion
 */

int snack_listen(int socket, int backlog);

// snack_listen with default backlog
int snack_default_listen(int socket);

#endif