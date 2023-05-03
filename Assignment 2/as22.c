#include<stdio.h>

int main()
{        
    int sum=0,n;
    printf("ASCII values of all characters including upper and lower both are as follows\n");
   
    printf("Upper characters: \n");
    for(int i='A';i<='Z';i++)
    {
        printf("%d\t",i);

    }

    printf("\nLower characters: \n");
    
    for(int i='a';i<='z';i++)
    {
        printf("%d\t",i);

    }
    printf("\n");

    return 0;
}    