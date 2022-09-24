#include "sort.h"

void sort(int arr[])
{

    if(arr == NULL)
        return;

    switch (sort_algorithm) {
        case BUBBLE_SORT:
            _bubble_sort(arr);
            break;
        case QUICK_SORT:
            _quick_sort(arr,0,sizeof(arr)-1);
            break;
        default:
            _bubble_sort(arr);
            break;
    }
}

static void _bubble_sort(int arr[])
{
    const unsigned int size = sizeof(arr);

    for(int i = 0; i < size;i++) {
        for(int j = 0; j < size - i - 1;j++) {
            if(arr[j+1] > arr[j]) {
                int tmp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

static void _quick_sort(int numbers[], int left, int right)
{
    int l_hold = left;
    int r_hold = right;
    int pivot = numbers[left];

    while (left < right) {
        while ((numbers[right] >= pivot) && (left < right))
            right--;
        if (left != right) {
            numbers[left] = numbers[right];
            left++;
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++;
        if (left != right) {
            numbers[right] = numbers[left];
            right--;
        }
    }

    numbers[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;

    if (left < pivot)
        _quick_sort(numbers, left, pivot-1);
    if (right > pivot)
        _quick_sort(numbers, pivot+1, right);
}




