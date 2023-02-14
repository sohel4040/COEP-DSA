#include<stdio.h>
#include<stdlib.h>

typedef struct stack
{
    int *arr;
    int top;
    int size;
} stack;

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
    if(isEmpty(*s))
    {
        s->top = 0;
        s->arr[s->top]= data;
    }

    s-> arr[s->top++] = data;
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
    for(int i= s.top-1; i>=0; i--)
    {
        printf("%d\t",s.arr[i]);
    }
    printf("\n");
}

int main()
{
    stack s;
    initstack(&s,10);
    push(&s,10);
    push(&s,20);
    push(&s,30);
    push(&s,40);

    display(s);
    pop(&s);
    display(s);
    return 0;
}
