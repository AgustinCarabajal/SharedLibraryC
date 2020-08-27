#include "thread.h"

void _thread_pool_create(void *( *func )()) {

    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&_thread_pool[i], NULL, func, NULL);
    }
}

void _thread_pool_destroy() {

    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_join(_thread_pool[i], NULL);
    }
}

