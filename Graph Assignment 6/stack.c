#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"stack.h"
#define MAX 100

void initstack(stack *S){
	S->A = (int*)malloc(sizeof(int) * MAX);
	S->s = MAX;
	S->top = -1;
	return;
}

void push(stack *S, int n){
	if(!S)
	  return;
	if(S->top == -1){
	  S->A[++S->top] = n;
	  return;
	}
	S->A[++S->top] = n;
	return;
}

int pop(stack *S){
	int e = -1;
	if(S->top == -1)
		return e;
        e = S->A[S->top--];
	return e;
}

int peek(stack S){
        if(S.top == -1)
          return INT_MIN;
	return (S.A[S.top]);
}

int isEmptyStack(stack S){
  return (S.top == -1);
}

