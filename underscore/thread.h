#ifndef THREAD_LIB
#define THREAD_LIB

// STANDARD LIBRARIES

#include <stdio.h>
#include <pthread.h>
#include "socket.h"

// DEFAULT VALUES

#define TRUE   1
#define FALSE  0
#define BACKLOG 5

typedef struct {
    int server;
    int client;
} _cdata;

// VARIABLES

_cdata *data;
pthread_t _tcon;

// FUNCTIONS

/**
 * METHOD: _thread
 * 
 * Permite manejar varias conexiones en diferentes threads
 * 
 * @params: 
 *      port -> Puerto en el que se van a escuchar las conexiones
 *      func -> Funcion custom a ejecutar en cada interaccion [use func(data)]
 *          data -> Informacion de los sockets de la conexion
 *      b_size -> Longitud maxima del string a recibir
 *
 * @example:
 *      Call with _thread("9000", myFunction);
 */
void _thread(char *port, void (*func)());

#endif