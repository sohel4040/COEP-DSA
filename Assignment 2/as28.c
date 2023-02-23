#include<stdio.h>

int checkPrime(int n)
{
  for(int i=2;i<n;i++)
  {
  	if(n%i==0)
  	  return -1;
  }
  
  return 1;
}

int main()
{
 
 for(int i=2;i<=100;i++)
 {
   if(checkPrime(i) == 1)
     printf("%d\t",i);
 }

 return 0;
}
