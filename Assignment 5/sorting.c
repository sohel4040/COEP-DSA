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
