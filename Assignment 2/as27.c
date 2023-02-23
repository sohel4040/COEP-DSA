#include<stdio.h>

int gcd(int a,int b)
{
 if(b==0)
  return a;
  
  return gcd(b, a%b);
}

int lcm(int a, int b)
{
 int g= gcd(a, b);
 
 return (a/g*b);
}


int main()
{
 printf("GCD of a number is %d\n",gcd(10,20));
 printf("LCM of a number is %d",lcm(10,20));
 return 0;
}
