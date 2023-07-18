#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//stack node
typedef struct stack{
	int *A;
	int s;
	int top;
}stack;

//functions
void initstack(stack *S);
void push(stack *S, int n);
int pop(stack *S);
int peek(stack S);
int isEmptyStack(stack S);