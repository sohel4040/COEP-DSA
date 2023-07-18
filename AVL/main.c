#include<stdio.h>
#include"avl.h"

int main()
{
    AVL t;
    initAVL(&t);
    insertNodeIntoAVL(&t, 1);
    insertNodeIntoAVL(&t, 2);
    insertNodeIntoAVL(&t, 3);
    insertNodeIntoAVL(&t, 4);
    insertNodeIntoAVL(&t, 5);
    insertNodeIntoAVL(&t, 6);
    insertNodeIntoAVL(&t, 7);
    insertNodeIntoAVL(&t, 8);
    insertNodeIntoAVL(&t, 9);





    inorder(t); printf("\n");
    printf("\n");

    // removeNodeIterative(&t, 10);
    // printf("Root node is : %d\n",t->data);
    // printf("After deletion of 10 : \n");
    // inorder(t);
    // printf("\n");


    // removeNodeIterative(&t, 4);
    // printf("Root node is : %d\n",t->data);
    // // printf("After deletion of 20 : \n");
    // inorder(t); printf("\n");

    // removeNodeIterative(&t, 3);
    // printf("Root node is : %d\n",t->data);
    // // printf("After deletion of 20 : \n");
    // inorder(t); printf("\n");

    // removeNodeIterative(&t, 6);
    // printf("Root node is : %d\n",t->data);
    // // printf("After deletion of 20 : \n");
    // inorder(t); printf("\n");
    // // printf("\n");

    // removeNodeIterative(&t, 5);
    // printf("Root node is : %d\n",t->data);
    // // printf("After deletion of 20 : \n");
    // inorder(t); printf("\n");
    // removeNodeIterative(&t, 2);
    // printf("Root node is : %d\n",t->data);
    // // printf("After deletion of 20 : \n");
    // inorder(t); printf("\n");

    // removeNodeIterative(&t, 1);
    // printf("Root node is : %d\n",t->data);
    // // printf("After deletion of 20 : \n");
    // inorder(t); printf("\n");

    // removeNodeIterative(&t, 8);
    // printf("Root node is : %d\n",t->data);
    // // printf("After deletion of 20 : \n");
    // inorder(t); printf("\n");
    // removeNodeIterative(&t, 60);
    // printf("Root node is : %d\n",t->data);
    // printf("After deletion of 60 : \n");
    // inorder(t);
    // printf("\n");

    // removeNodeIterative(&t, 50);
    // printf("Root node is : %d\n",t->data);
    // printf("After deletion of 50 : \n");
    // inorder(t);
    // printf("\n");

    // removeNodeIterative(&t, 30);
    // printf("Root node is : %d\n",t->data);
    // printf("After deletion of 30 : \n");
    // inorder(t);
    // printf("\n");

    // removeNodeIterative(&t, 40);
    // printf("After deletion of 40 : \n");
    // printf("After deletion of 30 : \n");
    // inorder(t);
    // printf("\n");

    // destroyTree(&t);
    // printf("Tree has been destroyed successfully\n");
    // inorder(t); printf("\n");
    // printf("\n");

    return 0;
}