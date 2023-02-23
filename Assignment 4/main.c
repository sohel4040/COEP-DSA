#include<stdio.h>

void printArray(int *a,int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d\t",a[i]);
	}
	
}
void swap(int *x, int *y)
{

 int temp=*x;
 *x=*y;
 *y=temp;
 
}
void bubbleSort(int *arr,int n)
{

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			  swap(&arr[j+1],&arr[j]);		    
		}
	}
}

void selectionSort(int *arr,int n)
{
	for(int i=0;i<n;i++)
	{
		int min=i;
		for(int j=i+1;j<n;j++)
		{
			if(arr[j]<arr[min])
			  min=j;
		}
		if(min!=i)
		swap(&arr[i],&arr[min]);
	}
}

void insertionSort(int *arr,int n)
{
	int val,j;

	for(int i=1;i<n;i++)
	{
		val=arr[i];
		j=i-1;
		while(j >= 0 && arr[j] > val)
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=val;
	}
}

int main()
{
    int arr[]={3,5,2,1,8,5,2,7};
    int size = sizeof(arr) / sizeof(int);
    int n;
    printf("Enter a choice : \n 1. Bubble sort \n 2. Selection sort \n 3. Insertion sort\n");
    scanf("%d",&n);

    switch(n)
    {
        case 1: bubbleSort(arr,size);
                break;
        case 2: selectionSort(arr,size);
                break;
        case 3: insertionSort(arr,size);
                break;
        default: printf("Invalid");
    }

    printArray(arr,size);

    return 0;
}