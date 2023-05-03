#include<stdio.h>
#include<stdlib.h>


typedef struct node 
{
    int data;
    struct node * next;    
} node;

typedef struct stack
{
    struct node* top;
} stack;

typedef struct queue
{
    stack s1, s2;
} queue;

void initstack(stack *s)
{
    s->top = NULL;
}

void initqueue(queue *q)
{
    initstack(&q->s1);
    initstack(&q->s2);
}

int isEmpty(stack s)
{
    return (s.top == NULL);
}

void push(stack *s,int data)
{
    node* newnode = (node*) malloc(sizeof(node));

    if(!newnode)
    return;

    newnode->data=data;
    newnode->next = NULL;

    if(isEmpty(*s))
    {
        s->top = newnode;
        return;
    }

    newnode -> next = s -> top;
    s -> top = newnode;

}

int pop(stack *s)
{
    if(isEmpty(*s))
    return -1;

    node * temp = s-> top;
    int element = s->top->data;
    s->top = s->top->next;
    free(temp);

    return element;
}

int top(stack s)
{
    return s.top->data;
}

void display(stack s)
{
    node *temp = s.top;

    while(temp)
    {
        printf("%d\t",temp->data);
        temp = temp -> next;
    }
}

void enqueue(queue *q, int data)
{
    push(&q->s1,data);
}

int dequeue(queue *q)
{
    while(!isEmpty(q->s1))
    {
        push(&q->s2,pop(&q->s1));
    }
    int element = pop(&q->s2);

    while(!isEmpty(q->s2))
    {
        push(&q->s1, pop(&q->s2));
    }

    return element;
}

int main()
{
    queue q;

    initqueue(&q);

    enqueue(&q,10);
    enqueue(&q,20);
    enqueue(&q,30);
    dequeue(&q);

    display(q.s1);

    return 0;
}