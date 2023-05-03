#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"aBST.h"

void initABST(aBST *t)
{   
    t -> array = NULL;
    t -> size = 0; 
    return;
}

void insertNodeIntoABST(aBST *t, int key)
{
    if(t -> array == NULL)
    {
        t -> array = (int*) malloc(sizeof(int));
        t -> array[0] = key;
        t -> size++;
        return;
    }

    int p = 0;

    while(p < t -> size && t -> array[p] != INT_MIN)
    {

        if(t -> array[p] > key)
            p = 2*p + 1;
        else if(t -> array[p] < key)
            p = 2*p + 2;
        else
            return;
    }

    if(t -> array[p] == INT_MIN)
    {
        t -> array[p] = key;
        return;
    }

    t -> array = realloc(t -> array, (p+1)*sizeof(int));

    if(!(t -> array))
        return;

    for(int i = t -> size; i < p; i++)
    {
        t -> array[i] = INT_MIN;
    }

    t -> array[p] = key;
    t -> size = p+1;

    return;
}

int heightOfTree(aBST t)
{
    int count = 0;

    if(t.size == 0)
        return count;

    for(int i = (t.size)-1; i > 0; i = (i-1)/2)
    {
        count++;
    }

    return ++count;
}

int countLeafNodes(aBST t)
{
    
    if(t.size == 0)
        return 0;

    if(t.size == 1)
        return 1;

    int p = (t.size)-1;
    int count = 0;
    int left, right;

    for(int i = p; i >= 0; i--)
    {
        if(t.array[i] == INT_MIN)
            continue;

        left = 2*i+1;
        right = 2*i+2;

        if((left > p && right > p) || (t.array[left] == INT_MIN && t.array[right] == INT_MIN))
            count++;

    }   
    return count;
}

int isComplete(aBST t)
{
    if(t.size == 0)
        return 0;

    int height = heightOfTree(t) - 1;

    int levelIndex = 0;
    int i = 0;

    while(i <  height)
    {
        levelIndex = levelIndex + 2*i;
        i++;
    }

    for(int i = levelIndex; i >=0; i--)
    {
        if(t.array[i] == INT_MIN)
            return 0;
    }

    return 1;
}

void levelOrderTraversal(aBST t)
{
    if(t.size == 0)
        return;

    int i = 0, j = 0;
    printf("%d\n",t.array[i]);

    while(i < t.size-1 && j < t.size-1)
    {
        i = 2*i+1;
        j = 2*j+2;

        for(int k = i; (k <= j) && (k < t.size); k++)
        {
            if(t.array[k] != INT_MIN)
                printf("%d\t",t.array[k]);
            else
                printf("\t");
        }    
        printf("\n");
    }
}

void inOrder(aBST t, int p)
{
    if(p >= t.size || t.array[p] == INT_MIN)
        return;

    inOrder(t, 2*p+1);
    printf("%d\t", t.array[p]);
    inOrder(t, 2*p+2);
}

