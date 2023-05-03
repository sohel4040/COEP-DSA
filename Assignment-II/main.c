#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"aBST.h"

int main()
{
    aBST t;
    initABST(&t);

    insertNodeIntoABST(&t, 10);
    insertNodeIntoABST(&t, 5);
    insertNodeIntoABST(&t, 20);
    insertNodeIntoABST(&t, 30);
    insertNodeIntoABST(&t, 15);
    insertNodeIntoABST(&t, 7);
    insertNodeIntoABST(&t, 2);
    insertNodeIntoABST(&t, 12);

    // inOrder(t, 0);

    printf("Height of the tree is : %d\n",heightOfTree(t));
    printf("Total leaf nodes are : %d\n",countLeafNodes(t));

    if(isComplete(t))
        printf("CBT\n");
    else
        printf("Not CBT\n");

    levelOrderTraversal(t);

    return 0; 
}