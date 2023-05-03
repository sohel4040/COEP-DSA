#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

void initstack(stack *s)
{
    s -> top = NULL;
}

int isEmpty(stack s)
{
    return (s.top == NULL);
}

void push(stack *s,int data)
{
    snode* newnode = (snode*) malloc(sizeof(snode));

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

    int element = s->top->data;
    snode * temp = s-> top;
    s->top = s->top->next;
    free(temp);

}

int top(stack s)
{
    
    return (s.top -> data);
}

void display(stack s)
{
    snode *temp = s.top;

    while(temp->next)
    {
        printf("%d\t",temp->data);
        temp = temp -> next;
    }
}