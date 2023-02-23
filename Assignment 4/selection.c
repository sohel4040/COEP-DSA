#include<stdio.h>

// Sohel Shamshuddin Bargir - 14223002
void printArray(int *arr,int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d\t",arr[i]);
	}
}

void swap(int *x, int *y)
{
	int temp=*x;
	*x=*y;
	*y=temp;
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

int main()
{
	int arr[]={134,112,2,54,6};
	int n = sizeof(arr)/sizeof(n);
	selectionSort(arr,n);
	printArray(arr,n);
	return 0;
}
