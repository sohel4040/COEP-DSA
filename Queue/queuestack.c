#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
    int *arr;
    int top;
    int size;
} stack;

typedef struct queue
{
    stack s1,s2;
    int size;
} queue;

void initstack(stack *s, int size)
{
    s-> arr= (int *)malloc(sizeof(int)*size);
    s-> top= -1;
    s-> size = size;
}
int isFull(stack s)
{
    return (s.top == s.size-1);
}
int isEmpty(stack s)
{
    return (s.top == -1);
}

void push(stack *s, int data)
{
    if(isFull(*s))
        return;
  	
    s-> arr[++s->top] = data;
    return;
}
int pop(stack *s)
{
    if(isEmpty(*s))
        return -1;
    
    int element = s->arr[s->top--];
    return element;
}

void display(stack s)
{
    for(int i = 0; i<= s.top; i++)
    {
        printf("%d\t",s.arr[i]);
    }
    printf("\n");
}

void initqueue(queue *q, int size)
{
    initstack(&q->s1, size);
    initstack(&q->s2, size);
    q->size = size;
}

void enqueue(queue *q, int data)
{
    push(&q->s1,data);
}

int dequeue(queue *q)
{
    int item;
    while(!isEmpty(q->s1))
    {
        int element = pop(&q->s1);
        push(&q->s2,element);
    }
    item = pop(&q->s2);
    while(!isEmpty(q->s2))
    {
        int element = pop(&q->s2);
        push(&q->s1,element);
    }
    return item;
}

int main()
{
    queue q;
    initqueue(&q,5);
    enqueue(&q,100);
    enqueue(&q,200);
    enqueue(&q,300);
    enqueue(&q,400);

    display(q.s1);
    dequeue(&q);
    display(q.s1);
    dequeue(&q);
    display(q.s1);
    enqueue(&q,500);
    display(q.s1);


    return 0;
}
