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
	int arr[]={134,112,2,54,6};
	int n = sizeof(arr)/sizeof(n);
	insertionSort(arr,n);
	printArray(arr,n);
	return 0;
}
