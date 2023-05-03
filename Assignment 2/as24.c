#include<stdio.h>

// Using recursion
void decimal(int n)
{
  if(n<=0)
    return;
    
  int d= n%2;
  decimal(n/2);
  printf("%d",d);
   
}

int main()
{

   int c;
   printf("Enter a decimal number to be converted into binary");
   scanf("%d",&c);
   
   int temp = c;
   
   // Using iteration
   /*while(temp>0)
   {
   	int d= temp%2;
   	printf("%d",d);
   	temp = temp /2;
   }*/
   
   decimal(c);
   
   printf("\n");
   
   return 0;
  

}
