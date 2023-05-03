#include<stdio.h>

#define SIZE 10

// Sohel Shamshuddin Bargir - 14223002
int swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void display(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%d\t",arr[i]);
    }
}
int main()
{
    int a[]={85,70,22,55,30};
    int size = sizeof(a)/sizeof(int);
    printf("Before reversing the array is:\n ");
    display(a,size);
    for(int i=0; i<(size/2);i++)
    {
        swap(&a[i],&a[size-1-i]);
    }

    printf("\nAfter reversing the array is:\n ");
    display(a,size);
    
    return 0;
}