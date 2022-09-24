#include "linkedlist.h"

void add(LinkedList *list,Node *node)
{
    if(_listExists(list))
        return NULL;

    if(list->first == NULL) {
        list->first = node;
        list->current = node;
    }
    else {
        list->last->next = node;
    }
    list->last = node;
}

Node* next(LinkedList *list) {
    if(_listExists(list))
        return NULL;

    if(!hasNext(list))
        return NULL;

    return hasNext(list) ? NULL : list->current->next;
}

Node* nextCyclical(LinkedList *list) {
    if(_listExists(list) || empty(list))
        return NULL;

    if(list->current == list->last) {
        list->current = list->first;
        return list->first;
    }

    list->current = list->current->next;
    return list->current;
}

u8 hasNext(LinkedList *list) {
    if(_listExists(list))
        return NULL;

    return empty(list) || list->current == list->last ? 0 : 1;
}

u8 empty(LinkedList *list) {
    if(_listExists(list))
        return NULL;

    return list->first == NULL;
}

u32 size(LinkedList *list) {
    if(_listExists(list))
        return NULL;

    return list->size != -1 ? list->size : _listSize(list->first);
}

static u8 _listExists(LinkedList *list) {
    return list == NULL ? 0 : 1;
}

static u32 _listSize(Node *node) {
    return node == NULL ? 0 : 1 + _listSize(node->next);
}

