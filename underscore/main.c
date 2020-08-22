#include <stdio.h>
#include <sys/socket.h>
#include "select.h"
#include "list.h"

void myFunction(int fd, char* msg) {
    char* text = malloc(sizeof(msg));
    printf("Message from %d: %s", fd, msg);
    // _enqueue((void*) msg);
    // text = (char*) _dequeue();
    // printf("Dequeued: %s", text);
}

int main() {

    _select("9000", myFunction, 1024);

    return 0;
}