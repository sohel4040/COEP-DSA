#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int data;
	struct node *next;
}node;


typedef node* List;

//Display all elements of linked list
void display(List l)
{
	if(!l){
	printf("\n");
	return;
	}
	while(l != NULL)
	{
		printf("%d\t",l->data);
		l=l->next;
	}
	printf("\n");
}

//Display alternate elements
void displayAlternate(List l)
{
	if(!l)
	return;
	
	while(l)
	{
		printf("%d\t",l->data);
	
		l=l->next;
		if(l)
		l = l -> next;
	}
	printf("\n");
}

//Delete last node from list
void deleteNode(List *l)
{
	
	List temp =*l;
	
	if(!((*l)->next))
	{
	*l=NULL;
	free(temp);
	return;
	}
	
	while(temp->next->next)
	{
	temp=temp->next;
		
	}
	List h=temp->next;
	temp->next=NULL;
	free(h);
	
}

//Counting number of elements 
int count(List l)
{
	
	int cnt=0;
	while(l)
	{
	cnt++;
	l=l->next;
	}
	return cnt;
	
}

// Checking if list is sorted or not
int checkifSorted(List l)
{
	List p=l;
	List q=l->next;
	while(p && q)
	{
	  if((p->data) >( q->data))
	  	return 0;
	  p=p->next;
	  q=q->next;
	}
	
	return 1;
}

// Inserting a element at the end of list
void append(List *l,int key)
{
	node *nn=(node*)malloc(sizeof(node));
	
	if(!nn)
	return;
	
	nn->data=key;
	nn->next=NULL;
	
	List p=*l;
	
	if(p==NULL)
	{
		*l=nn;
		return;
	}
	
	while(p->next)
	{
		p=p->next;
	}
	p->next=nn;
	
}

// Reversing the list
void reverse1(List *l)
{
	if(!*l || !((*l)->next))
	return;
	
	List p=NULL;
	List q=*l;
	
	while(q)
	{
	
		List temp = q->next;
		
		q->next=p;
		p=q;
		q=temp;
		
	}	
	*l =p;
	return;
}

// Pushing element in a stack
void insertAtFront(List *l,int key)
{
	node *nn=(node*)malloc(sizeof(node));
	
	if(!nn)
	return;
	
	nn->data=key;
	nn->next=NULL;
	
	nn->next=(*l);
	*l=nn;
	
}

// Insertion at specific position 
void insertAtPosition(List *l,int pos,int key)
{
	node *nn=(node*)malloc(sizeof(node));
	
	if(!nn)
	return;
	
	nn->data=key;
	nn->next=NULL;
	
	List p=*l;
	
	if(pos==1)
	insertAtFront(l,key);
	
	
	while((pos-2)>0)
	{
	 p=p->next;
	 pos--;
	}
	nn->next=p->next;
	p->next=nn;
	
}




void initList(List *l)
{ 
	*l=NULL;
	return;
}

int main()
{
	List a;
	initList(&a);
	append(&a,10);
	append(&a,20);
	append(&a,30);
	append(&a,40);
	display(a);
	printf("%d\n",checkifSorted(a));
	printf("%d\n",count(a));
	reverse1(&a);
	//insertAtPostion(&a,2,50);
	
	/*display(a);
	displayAlternate(a);
	deleteNode(&a);
	display(a);
	deleteNode(&a);
	display(a);
	deleteNode(&a);
	display(a);
	deleteNode(&a);
	display(a);
	deleteNode(&a);
	display(a);*/
	
	append(&a,100);
	insertAtPosition(&a,2,90);
	/*append(&a,200);
	append(&a,300);*/
	
	display(a);
	display(a);

	return 0;
}

