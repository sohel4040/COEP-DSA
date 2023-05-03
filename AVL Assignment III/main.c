#include<stdio.h>
#include<stdlib.h>
#include"avl.h"

int main()
{
    AVL t;
    initAVL(&t);

    FILE *ptr;
    ptr = fopen("data.txt","r");

    char data[20];
    for(int i=1;i<50;i++)
    {
        fscanf(ptr,"%s",data);
        // fgets(data, 20, ptr);
        insertNodeIntoAVL(&t, data);
    }
    while(1)
    {
        printf("1 . Remove name \n");
        printf("2 . Display inorder \n");
        printf("3 . Destroy the tree \n");
        printf("4 . Exit \n");

        int c;

        scanf("%d",&c);


        switch(c)
        {
            case 1: if(!t)
                        printf("Tree is empty !");
                    else
                    {      
                        char data1[20];
                        fscanf(stdin, "%s", data1);
                        printf("%s\n",data1);
                        removeNodeIterative(&t, data1);}
                    break;

            case 2: if(!t)
                        printf("Tree is empty !");
                    else
                        inorder(t);
                    printf("\n");
                    break;
            
            case 3: if(!t)
                        printf("Tree is empty !\n");
                    else
                        destroyTree(&t);
                    break;

            case 4: exit(0);
                    break;

            default: printf("Invalid choice\n");
        }

    }

    return 0;
}