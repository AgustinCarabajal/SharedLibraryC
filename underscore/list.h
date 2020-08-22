#ifndef LIST_LIB
#define LIST_LIB

struct node {
    struct node* next;
    void* data;
};
typedef struct node _node;

void _enqueue(void* data);
void* _dequeue();

#endif