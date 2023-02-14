#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"


void initList(List *l)
{
   *l = NULL;
}

void insertAtBeginning(List *l, int data)
{
    node *nn = (node*) malloc(sizeof(node));

    if(!nn)
        return;

    nn -> data = data;
    nn -> next = NULL;
    
    if(!(*l))
    {
        *l = nn;
        return;
    }

    nn -> next = (*l);
    *l = nn;
}

void insertAtMiddle(List *l, int data, int position)
{
    node *nn = (node*) malloc(sizeof(node));

    if(!nn)
	return;

    nn -> data = data;
    nn -> next = NULL;
    
    if(!(*l))
    {
        *l = nn;
        return;
    }

    node *temp = *l;

    for(int i=2;i <= position;i++)
    {
	 if(temp -> next != NULL)
	 	temp = temp -> next;
    }

    nn -> next = temp -> next;    
    temp -> next = nn;
}

void insertAtEnd(List *l, int data)
{
    node *nn = (node*) malloc(sizeof(node));

    if(!nn)
	return;

    nn -> data = data;
    nn -> next = NULL;
    if(!(*l))
    {
	*l = nn;
	return;
    }

    node *temp = *l;

    while(temp -> next)
    {
	temp = temp -> next;
    }

    temp -> next = nn;
}

int deleteFromBeginning(List *l)
{
     if(!(*l))
	 return -1;
     if(!(*l)->next)
     {
	*l = NULL;
	return -1;
     }

     node *temp = *l;
     int element = temp -> data;

     *l = (*l) -> next;

     free(temp);

     return element;
}

int deleteFromMiddle(List *l, int position)
{
    node *temp = *l;
    for(int i=2;i<=position;i++)
    {
	if(temp -> next != NULL)
	    temp = temp -> next;
    }

    node *toDelete = temp -> next;
    int element = toDelete -> data;
	
    temp -> next = temp -> next -> next;
    free(toDelete);
    return element; 
}

int deleteFromEnd(List *l)
{
     if(!(*l))
	return -1;

     if(!(*l)->next)
     {
	*l = NULL;
        return -1;
     }

     node *temp = *l;
     while(temp->next->next)
     {
	 temp = temp -> next;
     }

     node *toDelete = temp-> next;
     int element = toDelete -> data;
     temp -> next = NULL;

     free(toDelete);

     return element;	
}

int searchNode(List l, int key)
{
    node *temp = l;

    while(temp -> next)
    {
	if(temp -> data == key)
	  return 1;

	temp = temp -> next;
    }

    return 0;
}

void traverse(List l)
{
	node *temp = l;

	while(l)
	{
	   printf("%d\t",l -> data);
	   l = l -> next;	
	}
	printf("\n");	
	
}



