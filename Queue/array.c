#include<stdio.h>
#include<stdlib.h>

typedef struct queue
{
    int *arr;
    int size;
    int front;
    int rear;
} queue;

void initstack(queue *q, int size)
{
    q->arr =(int*)malloc(sizeof(int)*size);
    q->size = size;
    q->front = -1;
    q->rear = -1;
}

int isEmpty(queue q)
{
    return q.front == q.rear == -1;
}

int isFull(queue q)
{
    return q.rear == q. size;
}

void enqueue(queue *q, int data)
{
    if(isFull(*q))
        return;
    if(isEmpty(*q))
    {
        q->front = 0;
        q->rear = 0;
    }

    q->arr[q->rear++] = data;
}

int dequeue(queue *q)
{
    if(isEmpty(*q))
    return -1;

    if(q-> front == q-> rear)
    {
        int e = q->arr[q->front];
        q->front= -1;
        q->rear= -1;
        return e;
    }

    int element = q->arr[q->front++];	

    return element;

}

void display(queue q)
{

    for(int i=q.front; i < q.rear; i++)
    {
        printf("%d\t",q.arr[i]);
    }
    printf("\n");
}

int main()
{
    queue q;
    initstack(&q,5);
    enqueue(&q,10);
    enqueue(&q,20);
    enqueue(&q,30);
    display(q);
    dequeue(&q);
    display(q);
    enqueue(&q,40);
    display(q);

}   
