#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
} node;

typedef struct queue
{
    struct node* front;
    struct node* rear;
    int count;
} queue;

typedef struct stack
{
    queue q1, q2; 
} stack;

void initqueue(queue *q)
{
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
    return;
}

void initstack(stack *s)
{
    initqueue(&s->q1);
    initqueue(&s->q2);
}

int isEmpty(queue q)
{
    return (q.front == NULL || q.rear == NULL);
}

void enqueue(queue *q, int data)
{
    node *nn = (node*)malloc(sizeof(node));

    if(!nn)
        return;

    nn -> data = data;
    nn -> next = NULL;

    q-> count++;

    if(isEmpty(*q))
    {
        q -> front  = nn;
        q -> rear  = nn;
        return; 
    }

    q->rear -> next = nn;
    q -> rear = q-> rear -> next;

    return;
    

}

int dequeue(queue *q)
{
    if(isEmpty(*q))
    return -1;

    q-> count--;

    if(q-> front == q-> rear)
    {
        int element = q-> front -> data;
        q-> front = q-> rear = NULL;
        return element;
    }

    node * temp = q-> front;
    int element = temp -> data;
    q->front = q-> front -> next;
    free(temp);
    
    return element;

}

void display(queue *q)
{
    node * temp = q -> front;

    while(temp)
    {
        printf("%d\t",temp->data);
        temp = temp -> next;
    }
    printf("\n");

    return;

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
    initstack(&s);
    push(&s,10);
    push(&s,20);
    push(&s,30);

    pop(&s);
    pop(&s);

    display(&s.q1);

    return 0;
}