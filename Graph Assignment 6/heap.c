#include"heap.h"
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

void initHeap(Heap *t)
{
    t->arr = (edge**) malloc(sizeof(edge*)); 
    if(!(t->arr))
        return;
    t->size = 1;
    t->rear = -1;
    return;
}


void insert(Heap *h, edge* e)
{
    if(!(h -> arr))
        return;
   
    if(isFullHeap(*h))
    {
        h->size *= 2;
        h->arr = (edge**) realloc(h->arr, sizeof(edge*)*(h->size));
    }

    h->arr[++h->rear] = e;
    int i = h -> rear;

    while(i > 0)
    {
        // if child is greater then go to the parent
        if(h->arr[i]->weight < h->arr[(i-1)/2]->weight)
        {
            // swapping done
            edge* temp = h->arr[i];
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

edge* removeFromHeap(Heap *h)
{
    if(!(h -> arr))
        return NULL;

    if(isEmptyHeap(*h))
        return NULL;

    edge* element = h->arr[0];
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
            if(h->arr[il]->weight < h->arr[ir]->weight)
                max = il;
            else
            {
            
                max = ir;
            }
        }
        if(h->arr[i]->weight < h->arr[max]->weight)
            return;
        else{
            
            edge* temp = h->arr[max];
            h->arr[max] = h->arr[i];
            h->arr[i] = temp;
            i = max;
        }

        il = 2 * i + 1;
        ir = 2 * i + 2;

    }

}

void traverse(Heap h)
{
    for(int i = 0; i <= h.rear; i++)
    {
        edge *e = h.arr[i];
        printf("%c->%c->%d\n",e->from, e->to, e->weight);
    }
    printf("\n");
}