#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"queue.h"

void initqueue(queue *Q){
	Q->front = NULL;
	Q->rear = NULL;
	Q->count = 0;
	return;
}

int isEmptyQueue(queue Q){
        return (Q.front == NULL || Q.rear == NULL);
}

void enqueue(queue *Q, int k){
	node*nn;
	nn = (node*)malloc(sizeof(node));
	if(!nn)
		return;
	nn->data = k;
	nn->next = NULL;
	if(isEmptyQueue(*Q)){
		Q->front = nn;
		Q->rear = nn;
		Q->count++;
		return;
	}
	Q->rear->next = nn;
	Q->rear = nn;
	Q->count++;
	return;
}

//remove an element from the queue
int dequeue(queue *Q){
	int e = INT_MIN;
	if(isEmptyQueue(*Q))
		return e;
	node*p = Q->front;
	Q->front = p->next;
	e = p->data;
	Q->count--;
	free(p);
	return e; 
}