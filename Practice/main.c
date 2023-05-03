#include<stdio.h>

#ifndef TREE 
#define TREE
#include"tree.h"
#endif

int main()
{
    Tree t;
    initTree(&t);

    insertNode(&t, 10);
    insertNode(&t, 1);
    insertNode(&t, 5);
    insertNode(&t, 40);
    insertNode(&t, 50);
    insertNode(&t, 45);
    insertNode(&t, 30);

    inOrderTraversal(t);
    printf("\n");
    inOrderTraverseIterative(t);

    // if(searchAnElement(t,1))
        // printf("The element is present\n");
    // else
        // printf("The element is not present\n");

    removeNode(&t,10);

    inOrderTraversal(t);
    printf("\n");

    return 0;
}