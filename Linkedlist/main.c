#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"

int main()
{
    List l;
    initList(&l);

    insertAtBeginning(&l,10);
    insertAtBeginning(&l,20);
    insertAtBeginning(&l,50);
    
    insertAtMiddle(&l,100,1);
    insertAtEnd(&l,200);
    deleteFromBeginning(&l);
    deleteFromMiddle(&l, 1);
    deleteFromEnd(&l);
    traverse(l);
    insertAtMiddle(&l,69,2);
    insertAtMiddle(&l,80,1);
    traverse(l);    
    return 0;
}
