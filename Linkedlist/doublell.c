#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
    int data;
    struct node * next;
    struct node * prev;
} node;
typedef node* List;

void initList(List *l)
{
    *l = NULL;
}

void append(List *l, int data)
{
    node * nn = (node*)malloc(sizeof(node));

    if(!nn)
    return;

    nn -> data = data;
    nn -> next = NULL;
    nn -> prev = NULL;

    if(*l == NULL)
    {
        *l = nn;
        return;
    }

    node * temp = *l;
    while(temp->next)
    {
        temp = temp -> next;
    }
    temp -> next = nn;
    nn -> prev = temp;

}

int deleteAtFront(List *l)
{
    if(!(*l))
        return -1;

    node * temp = *l;
    int element = temp -> data;
    if(!((*l)->next))
    {
        *l = NULL;
        free(temp);
        return element;
        
    }
    
    *l = (*l) -> next;
    *l -> prev = NULL;

    free(temp);

    return element;

}

void display(List l)
{
    node * temp = l;
    
    while(temp)
    {
        printf("%d\t",temp->data);
        temp = temp -> next;
    }
    printf("\n");
}

int deleteAtBack(List *l)
{
    if(!((*l)->next))
    {
        *l = NULL; 
        return -1; 
    }
    node * temp = *l;
    while(temp->next->next)
    {
        temp = temp ->next;
    }
    node *toDelete = temp->next;
    int element = toDelete->data;
    temp ->next = NULL;
    free(toDelete);
    return element;
}
int main()
{
    List l;
    initList(&l);
    append(&l,100);
    append(&l,200);
    append(&l,300);
    append(&l,400);
    append(&l,500);

    display(l);
    deleteAtFront(&l);

    display(l);
    deleteAtBack(&l);
    display(l);



    return 0;
}