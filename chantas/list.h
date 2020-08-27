// DO NOT USE - insecure methods

#ifndef LIST_LIB
#define LIST_LIB

#include <stdlib.h>
#include <stdio.h>

struct node {
    struct node* next;
    void* data;
};
typedef struct node _node;

void _enqueue(void* data);
void* _dequeue();

#endif