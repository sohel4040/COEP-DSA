#include"heap.h"
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

void initHeap(Heap *t)
{
    t->arr = malloc(sizeof(int)); 
    if(!(t->arr))
        return;
    t->size = 1;
    t->rear = -1;
    return;
}

// void initHeap(Heap *t)
// {
//     t->arr = malloc(sizeof(int)*size); 
//     if(!(t->arr))
//         return;
//     t->size = size;
//     t->rear = -1;
//     return;
// }

void insert(Heap *h, int data)
{
    if(!(h -> arr))
        return;
   
    // if(isFullHeap(*h))
    //     return;
    
    if(isFullHeap(*h))
    {
        h->size *= 2;
        h->arr = (int*) realloc(h->arr, sizeof(int)*(h->size));
    }

    h->arr[++h->rear] = data;
    int i = h -> rear;

    while(i > 0)
    {
        // if child is greater then go to the parent
        if(h->arr[i] > h->arr[(i-1)/2])
        {
            // swapping done
            int temp = h->arr[i];
            h->arr[i] = h->arr[(i-1)/2];
            h->arr[(i-1)/2] = temp;

            // go to parent
            i = (i-1)/2;
        }
        else
            return;
    }
    return;

}

int isEmptyHeap(Heap h)
{
    return h.rear == -1;
}

int isFullHeap(Heap h)
{
    return h.rear == (h.size)-1;
}

int removeFromHeap(Heap *h)
{
    if(!(h -> arr))
        return INT_MIN;

    if(isEmptyHeap(*h))
        return INT_MIN;

    int element = h->arr[0];
    h->arr[0] = h->arr[h->rear];
    h->rear--;

    heapify(h);

    return element;
}

void heapify(Heap *h)
{
    int i = 0;
    int il, ir;
    int max;
    il = 2 * i + 1;    
    ir = 2 * i + 2;    
    while(il <= h->rear)
    {
        if(ir > h->rear)
            max = il;
        else{
            if(h->arr[il] > h->arr[ir])
                max = il;
            else
                max = ir;
        }
        if(h->arr[i] > h->arr[max])
            return;
        else{
            int temp = h->arr[max];
            h->arr[max] = h->arr[i];
            h->arr[i] = temp;
            i = max;
        }

        il = 2 * i + 1;
        ir = 2 * i + 2;

    }

}

void heapsort(Heap *h)
{
    int total = h->rear;
    int temp;
    while(h->rear > 0)
    {
        temp = removeFromHeap(h);

        h->arr[h->rear+1] = temp;

    }
    h->rear = total;
}

void traverse(Heap h)
{
    for(int i = 0; i <= h.rear; i++)
    {
        printf("%d\t", h.arr[i]);
    }
    printf("\n");

    return;
}