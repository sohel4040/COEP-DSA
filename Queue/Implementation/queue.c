#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

void initqueue(queue *q)
{
    q->front = NULL;
    q->rear = NULL;
    return;
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

    if(q-> front == q-> rear)
    {
        q-> front = q-> rear = NULL;
        return -1;
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
