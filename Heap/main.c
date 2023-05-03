#include<stdio.h>
#include<stdlib.h>
#include"heap.h"



int main()
{
    Heap h;
    initHeap(&h);
    insert(&h, 20);
    insert(&h, 10);
    insert(&h, 30);
    insert(&h, 50);
    insert(&h, 100);
    insert(&h, 120);
    insert(&h, 150);

    // printing the heap
    printArray(h.arr, h.size);

    // Deleting 150 top element
    printf("Deleted Element : %d\n",deleteFromHeap(&h));

    printArray(h.arr, h.size);

    // Deleting 120 top element
    printf("Deleted Element : %d\n",deleteFromHeap(&h));

    printArray(h.arr, h.size);

    // Deleting 100 top element
    printf("Deleted Element : %d\n",deleteFromHeap(&h));

    printArray(h.arr, h.size);

    // Deleting 50 top element
    printf("Deleted Element : %d\n",deleteFromHeap(&h));

    printArray(h.arr, h.size);

    // Deleting 30 top element
    printf("Deleted Element : %d\n",deleteFromHeap(&h));

    printArray(h.arr, h.size);

    // Deleting 20 top element
    printf("Deleted Element : %d\n",deleteFromHeap(&h));

    printArray(h.arr, h.size);

    // Deleting 10 top element
    printf("Deleted Element : %d\n",deleteFromHeap(&h));

    printArray(h.arr, h.size);
  
    // Heap is empty , hence INT_MIN will be returned   
    printf("Deleted Element : %d\n",deleteFromHeap(&h));

    printArray(h.arr, h.size);

    return 0;

}