#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedList LinkedList;
typedef struct Node Node;

typedef struct LinkedList{
    Node *first;
    Node *last;
} LinkedList;

typedef struct Node{
    struct Node *next; // pointer to next node
    void *data; // pointer to some data
} Node;

void add(LinkedList*,Node*);



#endif