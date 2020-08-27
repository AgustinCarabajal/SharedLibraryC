// DO NOT USE - insecure methods

#include "list.h"

_node* head = NULL;
_node* tail = NULL;

void _enqueue(void* data) {
    _node* temp = malloc(sizeof(_node));
    temp -> data = data;
    temp -> next = NULL;
    if (tail == NULL) {
        head = temp;
    } else {
        tail -> next = temp;
    }
    tail = temp;
}

void* _dequeue() {
    if (head == NULL) {
        return NULL;
    } else {
        void* result = head -> data;
        _node* temp = head;
        head = head -> next;
        if (head == NULL) {
            tail = NULL;
        }
        free(temp);
        return result;
    }
}

void _printl() {
    _node* temp = malloc(sizeof(_node));
    temp = head;
    while (temp) {
        printf("%s", temp -> data);
        temp = temp -> next;
    }
    free(temp);
}