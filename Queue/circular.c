#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct queue
{
    int *arr;
    int front;
    int rear;
    int count;
    int size;
} queue;

void initstack(queue *q, int size)
{
    q->arr= (int*)malloc(sizeof(int)*size);
    q->front = -1;
    q->rear = -1;
    q->count = 0;
    q->size = size;

    return;
}

int isFull(queue q)
{
    return (q.count == q.size);
}

int isEmpty(queue q)
{
    return (q.count == 0);
}
void enqueue(queue *q , int data)
{
    if(isFull(*q))
        return;
    if(isEmpty(*q))
    {
        q->front = q->rear = 0;
        q->arr[q->rear] = data;
        q->count ++;

        return;
    }

    if(!isFull(*q))
    {
        q->rear = (q->rear+1) % q->size;
        q->arr[q->rear] = data;
        q->count ++;
        return;
    }
}

int dequeue(queue *q)
{
    if(isEmpty(*q))
        return -1;

    else
    {
    int element = q->arr[q->front];
    q->arr[q->front] = INT_MIN;
    q->front = ((q->front+1)%q->size);
    q->count--;
    return element;
    }
    
}
void display(queue q)
{
    for(int i= 0; i< q.size;i++)
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
    enqueue(&q,40);
    enqueue(&q,50);
    enqueue(&q,60);




    display(q);
    dequeue(&q);
    display(q);
    dequeue(&q);
    display(q);
    enqueue(&q,60);
    display(q);

    dequeue(&q);
    display(q);
    dequeue(&q);
    display(q);
    enqueue(&q,100);
    enqueue(&q,200);
    enqueue(&q,300);

    display(q);

    return 0;
}