#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

int main()
{
    queue q;
    initqueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    dequeue(&q);
    display(&q);
    dequeue(&q);
    display(&q);
    dequeue(&q);
    display(&q);

    return 0;
}


