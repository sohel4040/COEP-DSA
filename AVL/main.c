#include<stdio.h>
#include"avl.h"

int main()
{
    AVL t;
    initAVL(&t);
    insertNodeIntoAVL(&t, 10);
    insertNodeIntoAVL(&t, 20);
    insertNodeIntoAVL(&t, 30);
    insertNodeIntoAVL(&t, 40);
    insertNodeIntoAVL(&t, 50);
    insertNodeIntoAVL(&t, 70);
    insertNodeIntoAVL(&t, 80);
    insertNodeIntoAVL(&t, 90);
    insertNodeIntoAVL(&t, 5);
    insertNodeIntoAVL(&t, 2);
    insertNodeIntoAVL(&t, 3);
    insertNodeIntoAVL(&t, 6);
    insertNodeIntoAVL(&t, 200);
    insertNodeIntoAVL(&t, 300);



    inorder(t);
    printf("\n");

    // removeNodeIterative(&t, 10);
    // printf("Root node is : %d\n",t->data);
    // printf("After deletion of 10 : \n");
    // inorder(t);
    // printf("\n");


    // removeNodeIterative(&t, 20);
    // printf("Root node is : %d\n",t->data);
    // printf("After deletion of 20 : \n");
    // inorder(t);
    // printf("\n");

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

    destroyTree(&t);
    printf("Tree has been destroyed successfully\n");
    inorder(t);
    printf("\n");

    return 0;
}