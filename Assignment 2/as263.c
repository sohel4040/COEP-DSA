#include<stdio.h>

int main()
{
 int n;
 printf("Enter a number : ");
 scanf("%d", &n);
 
 for(int i =0 ; i< n ; i++)
 {
 	for(int j=0;j<=i;j++)
 	{
 		printf("*");
 	}
 	
 	for(int k=n;k<i;k--)
 	{
 		printf(" ");
 	}
 	
 	for(int l=0;l<=i;l++)
 	{
 		printf("*");
 	}
 	
 	printf("\n");
 }
 
 return 0;
}
