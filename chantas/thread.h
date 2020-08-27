#ifndef THREAD_LIB
#define THREAD_LIB

// STANDARD LIBRARIES

#include <pthread.h>

// DEFAULT VALUES

#define THREAD_POOL_SIZE 20

// VARIABLES

pthread_t _thread_pool[THREAD_POOL_SIZE];
// pthread_mutex_t _thread_pool_mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t _thread_pool_condition = PTHREAD_COND_INITIALIZER;

// FUNCTIONS

/**
 * METHOD: _thread_pool_create
 * 
 * Permite crear una thread pool del tamaño especificado en THREAD_POOL_SIZE
 * 
 * @params: 
 *      func -> Funcion custom a ejecutar en cada iteracion [use func()]
 *
 * @example:
 *      Call with _thread_pool_create(myFunction);
 */
void _thread_pool_create(void *( *func )());

/**
 * METHOD: _thread_pool_destroy
 * 
 * Permite eliminar la thread pool una vez hayan terminado de trabajar los threads
 *
 * @example:
 *      Call with _thread_pool_destroy();
 */
void _thread_pool_destroy();

#endif