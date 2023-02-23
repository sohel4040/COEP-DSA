#include<stdio.h>
#include<limits.h>
#include<math.h>

// Sohel Shamshuddin Bargir - 14223002
int min(int a,int b){
	return a < b ? a : b;
}
int max(int a,int b){
    return a > b ? a : b;

}
void findNearestSmallerAndGreater(int arr[],int n,int key){
	int i = 0 ;
	int j = n;
	int greater = -1;
	int smaller = -1;
	int k;
	for( k = 0 ; k < n ; k++)
	{
		if(arr[k] == key )
		break;
	}
	if(k-1 != n)
	greater = arr[k+1];
	if(k > 0)
	smaller = arr[k-1];

	printf("Nearest Greater element is : %d ",max(greater,smaller));
	printf("\nNearest Smaller element is : %d\n",min(greater,smaller));
}

int main(){
	int A[5] = {3,5,1,8,1};
	int n = 5;
	
	findNearestSmallerAndGreater(A,n-1,3);
	return 0;
}	