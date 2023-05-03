#include<stdio.h>

int main()
{        
    int sum=0,n;
    printf("Enter the number\n");
    scanf("%d",&n);
   
    // Using while loop    
    // while(n>0)
    // {
    //     sum = sum + n;
    //     n--;
    // }

    // Using for loop 
    for(int i=0;i<=n;i++)
    {
        sum = sum + i;

    }

    printf("The sum of first %d natural numbers is %d\n", n, sum);
    return 0;
}    