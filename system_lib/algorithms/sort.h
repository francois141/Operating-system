#ifndef SORT_H
#define SORT_H

#include "../../cpu/types.h"

enum SORT_TYPES {
        BUBBLE_SORT = 0,
        QUICK_SORT = 1,
};

const enum SORT_TYPES sort_algorithm = QUICK_SORT;

void sort(int arr[]);

static void _bubble_sort(int arr[]);
static void _quick_sort(int arr[],int left, int right);

#endif