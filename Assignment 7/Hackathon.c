#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "Hackathon.h"

void initList(Club *c)
{
    *c = NULL;
     return;
}

void AddMember(Club *c,int prn, char name[])
{
    student* s=(student*) malloc(sizeof(student));
    if(!s)
        return;
    s->prn=prn;
    strcpy(s->name,name);
    s->next = NULL;

    student* temp= *c;

    if(!temp)
    {
        *c = s;
        return;
    }
    s -> next = temp -> next;
    temp -> next = s;

    return;

}

void deleteMember(Club *c,int prn)
{
    student *prev = *c;
    student *curr = (*c)->next;

    if(!curr)
        return;

    student* temp;
    
    if(prev->prn == prn)
    {
        *c = curr;  
        return;      
    }

    while((curr->prn != prn) && curr)
    {
        prev = curr;
        curr = curr -> next;
    }

    student *f = prev -> next;
    prev -> next = curr -> next;
    curr -> next = NULL;
    free(f);
    return;
}

void display(Club c)
{
    Club temp = c;

    while(temp)
    {
        printf("%d\t",temp->prn);
        temp = temp -> next;
    }
    return;
}

int count(Club c)
{
    Club temp = c;
    int count = 0;

    while(temp)
    {
        count++;
        temp = temp->next;
    }
    return count > 2 ? count - 2 : 0;
}