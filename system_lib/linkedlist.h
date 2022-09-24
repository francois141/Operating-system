#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../cpu/types.h"

typedef struct LinkedList LinkedList;
typedef struct Node Node;

typedef struct LinkedList{
    Node *first;
    Node *current;
    Node *last;
    u32 size;
} LinkedList;

typedef struct Node{
    struct Node *next; // pointer to next node
    void *data; // pointer to some data
} Node;

void add(LinkedList*,Node*);

Node* next(LinkedList* list);
Node* nextCyclical(LinkedList *list);

u8 hasNext(LinkedList* list);

u8 empty(LinkedList* list);
u32 size(LinkedList* list);

static u8 _listExists(LinkedList *list);
static u32 _listSize(Node *node);

#endif