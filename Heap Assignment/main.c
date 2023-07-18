#include<stdio.h>
#include<stdlib.h>
#include"heap.h"

int main()
{
    Heap h;
    initHeap(&h);
    insert(&h, 50);
    insert(&h, 55);
    insert(&h, 53);
    insert(&h, 52);
    insert(&h, 58);
    insert(&h, 59);
    insert(&h, 90);
    insert(&h, 554);
    insert(&h, 564);
    insert(&h, 514);
    insert(&h, 549);


    // traverse(h);

    // printf("Element is %d\n",removeFromHeap(&h));
    // traverse(h);
    // traverse(h);

    // removeFromHeap(&h);
    heapsort(&h);

    traverse(h);
    // traverse(h);

    return 0;

}