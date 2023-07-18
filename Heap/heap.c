#include"heap.h"
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

void initHeap(Heap *t)
{
    t->arr = NULL; 
    t->size = 0;
    return;
}

void insert(Heap *t, int data)
{
    if(t->arr == NULL)
    {
        t -> arr =(int*) malloc(sizeof(int));
        t -> arr[0] = data;
        t -> size++;
        return;
    }

    t -> arr = realloc(t -> arr, ((t->size)+1)*sizeof(int));

    if(!(t -> arr))
        return;

    t -> arr[t->size] = data;
    t -> size++;
    
    int j = t->size-1;
    int i = (j-1)/2;

    while(i != 0)
    {
        if(t->arr[i] < t->arr[j])
        {
            int temp = t -> arr[i];
            t -> arr[i] = t -> arr[j];
            t -> arr[j] = temp;
        }
        j = i;
        i = (j-1)/2;
    }

    if(t->arr[i] < t->arr[j])
    {
            int temp = t -> arr[i];
            t -> arr[i] = t -> arr[j];
            t -> arr[j] = temp;
    }
    return;

}

int deleteFromHeap(Heap *t)
{
    if(!(t -> arr))
        return INT_MIN;

    if(t -> size == 1)
    {
        int element = t -> arr[0];
        t -> arr = NULL;
        t -> size--;
        return element;
    }

    int element = t -> arr[0];
    int lastElement = t -> arr[t -> size-1];

    t -> arr = realloc(t -> arr, ((t->size)-1)*sizeof(int));
    t -> size--;

    t -> arr[0] = lastElement;

    int lastIndex = t -> size -1;
    int i = 0;
    int j = (2*i)+2;
    while(j <= lastIndex)
    {
        if(t -> arr[i] < t -> arr[j])
        {
            int temp = t -> arr[i];
            t -> arr[i] = t -> arr[j];
            t -> arr[j] = temp;
        }

        i = j;
        j = (2*i)+2;
    }

    i = 0;
    j = (2*i)+1;
    while(j <= lastIndex)
    {
        if(t -> arr[i] < t -> arr[j])
        {
            int temp = t -> arr[i];
            t -> arr[i] = t -> arr[j];
            t -> arr[j] = temp;
        }

        i = j;
        j = (2*i)+2;
    }
    return element;
}

void printArray(int *arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    return;
}
