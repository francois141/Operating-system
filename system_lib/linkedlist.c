#include "linkedlist.h"

void add(LinkedList *list,Node *node)
{
    if(list->first == 0) 
    {
        list->first = node;
        list->last  = list->first;
    }
    else
    {
        list->last->next = node;
        list->last = node;
    }
}