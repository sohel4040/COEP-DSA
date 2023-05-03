#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"tree.h"
#include"stack.h"

void initTree(Tree *t)
{
    *t = NULL;
    return;
}

void insertNode(Tree *t, int data)
{

    node* n = (node*) malloc(sizeof(node));
    n -> data = data;
    n -> left = n -> right = NULL;

    if(!n)
        return;

    if(!(*t))
    {
        *t = n;
        return;
    }

    node* temp = *t;

    if(temp -> data > data)
        insertNode(&(temp -> left), data);
    else if(temp -> data < data)
        insertNode(&(temp -> right), data);
    else 
        return;
    return;
}

int searchAnElement(Tree t, int key)
{
    if(!t)
        return 0;

    node *temp = t;

    if(temp -> data == key)
        return 1;
    else if(temp -> data > key)
        searchAnElement(temp -> left, key);
    else
        searchAnElement(temp -> right, key);

}

node* removeNode(Tree *t, int key)
{
    node* temp = *t;

    if(temp ==  NULL)
        return temp;
    else if(temp -> data > key)
        temp -> left = removeNode(&(temp -> left), key);
    else
        temp -> right = removeNode(&(temp -> right), key);
}

void inOrderTraversal(Tree t)
{
    if(!t)
        return;
    
    inOrderTraversal(t -> left);
    printf("%d\t", t -> data);
    inOrderTraversal(t -> right);    
}

//         1
//     2       4
// 7      3 5       9
//     7   8
void inOrderTraverseIterative(Tree t)
{
    stack st;
    initstack(&st);
    
    node *p = t;
    while(p)
    {
        while(p -> left)
        {
            push(&st, p -> data);
            p = p -> left;
        }

        int data = pop(&st);
        printf("%d\t", data);

        if(!p -> right)
            p = p -> right;
        else
        {
            int d = pop(&st);
            printf("%d\t", d);
        }
    }
}

void preOrderTraversal(Tree t)
{
    if(!t)
        return;
    
    printf("%d\t", t -> data);
    preOrderTraversal(t -> left);
    preOrderTraversal(t -> right);
}

void postOrderTraversal(Tree t)
{
    if(!t)
        return;
    
    postOrderTraversal(t -> left);
    postOrderTraversal(t -> right);
    printf("%d\t", t -> data);
}
        // 10
    // 1      40
//       5        45
//                    50

