#include<stdio.h>

// Sohel Shamshuddin Bargir - 14223002
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
int main()
{

	int arr[]={2,43,10,5,3};
	int n=sizeof(arr)/sizeof(int);
	bubbleSort(arr,n);
	
	printArray(arr,n);
	
	return 0;
}
