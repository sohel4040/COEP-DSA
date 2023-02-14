#include<stdio.h>
#include<stdlib.h>

typedef struct queue
{
    int *arr;
    int size;
    int front;
    int rear;
    int count;
} queue;

typedef struct stack
{
    queue q1, q2; 
} stack;


void initqueue(queue *q, int size)
{
    q->arr =(int*)malloc(sizeof(int)*size);
    q->size = size;
    q->front = -1;
    q->rear = -1;
    q->count = 0;
}

void initstack(stack *s ,int size)
{
    initqueue(&s->q1,size);
    initqueue(&s->q2,size);
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
    q-> count++;
    
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

    q-> count--;
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

void push(stack *s, int data)
{
    enqueue(&s->q1, data);
}

int pop(stack *s)
{

    while(s->q1.count != 1)
    {
        enqueue(&s->q2,dequeue(&s->q1));
    }

    int element = dequeue(&s->q1);


    while(s->q2.count != 0)
    {
        enqueue(&s->q1,dequeue(&s->q2));
    }


    return element;
}

int main()
{
    stack s;
    initstack(&s,5);
    push(&s,10);
    push(&s,20);
    push(&s,30);

    pop(&s);

    display(s.q1);

    return 0;
}