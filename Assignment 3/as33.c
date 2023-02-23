#include<stdio.h>

// Sohel Shamshuddin Bargir - 14223002
int main()
{
    int a[] = {20,500,60,100,40};
    int size = sizeof(a)/sizeof(int); 
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size-i;j++)
        {
            printf("%d\t",a[j]);
        }
        printf("\n");
    }
   
    return 0;
}