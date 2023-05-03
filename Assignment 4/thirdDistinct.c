#include<stdio.h>

// Sohel Shamshuddin Bargir - 14223002
void swap(int *x, int *y)
{

 int temp=*x;
 *x=*y;
 *y=temp;
 
}
int findThirdDistinctElement(int *arr,int n)
{
    int thirdDistinct=-1;
	for(int i=0;i<3;i++)	
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			  swap(&arr[j+1],&arr[j]);		    
		}
	}

	int flag = 0;
	if(n>=3)
	{
		int temp = arr[n-3];
		for(int i=n-1;i>n-3;i--)
		{
			if(temp == arr[i])
				flag = 1;
		}
	}
	
	if(flag == 1)
		return arr[n-4];
    
	return n>=3 ? arr[n-3] : 0;
}

int main()
{

	int arr[]={2,2,3,1};
	int n=sizeof(arr)/sizeof(int);
	int num = findThirdDistinctElement(arr,n);
	if(num)
    {
        printf("Third Distinct Maximum element is %d\n",num);
    }
    else 
    {
        printf("The third distinct maximum does not exist, so the maximum element is %d\n",arr[n-1]);
    }
		
	return 0;
}
