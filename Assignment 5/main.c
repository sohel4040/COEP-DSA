#include<stdio.h>
#include "searching.h"
#include "sorting.h"
#include<stdlib.h>

void printArray(int arr[],int n)
{
    for(int i=0;i < n;i++)
    {
        printf("%d\t",arr[i]);
    }
    printf("\n");
}


int main()
{
    int a1[]= {3,522,343,5,3,2};
    int a2[]= {2,13,5,6,7,8,9};
    int n1= sizeof(a1)/sizeof(int);
    int n2= sizeof(a2)/sizeof(int);

    int p = linearSearch(a1,n1,343);
    if(p != -1)
        printf("Element is found at location %d\n",p);
    else 
        printf("Element is not found in an array\n");

    int b = binarySearch(a2,n2,6);
    if(b != -1)
        printf("Element is found at location %d\n",b);
    else 
        printf("Element is not found in an array or the array is not sorted\n");

    printf("Bubble sort:\n");
    bubbleSort(a1,n1);
    printArray(a1,n1);

    printf("Insertion sort:\n");

    int a3[]= {10,2,4,3,12,5};
    int n3= sizeof(a3)/sizeof(int);
    insertionSort(a3,n3);
    printArray(a3,n3);

    printf("Selection sort:\n");

    int a4[]= {50,220,20,10,5,9};
    int n4= sizeof(a4)/sizeof(int);
    insertionSort(a4,n4);
    printArray(a4,n4);
    return 0;
}
