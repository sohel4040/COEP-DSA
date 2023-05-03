#include"stack.h"
#include<stdlib.h>

void initStack(stack *s,int n)
{
        s-> A = (char*)malloc(sizeof(char)*n);
        s-> n = n;
        s-> top = -1;
}

int isFull(stack s)
{
    return (s.top == s.n-1);
}

int isEmpty(stack s)
{
    return (s.top == -1);
}

void push(stack *s,char c)
{
    if(isFull(*s))
        return;
    s->A[++(s->top)] = c;

}

char pop(stack *s)
{
    if(isEmpty(*s))
        return -1;
    return s->A[(s->top)--];
}

char peek(stack s)
{
    return s.A[s.top];
}