#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

void initstack(stack *s)
{
    s->top = NULL;
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

    int element = s->top->data;
    node * temp = s-> top;
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