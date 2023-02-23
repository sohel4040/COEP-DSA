#include<stdio.h>

int main()
{        
    // 54823 = 5+8+3
    int n,sum=0;
    printf("Enter the number\n");
    scanf("%d",&n);
   
    int temp=n;
    int count=1;

    int rev=0;
    while(temp>0)
    {
        int digit = temp % 10;
        rev = rev *10 + digit;
        temp = temp / 10;
    }
    printf("%d\n",rev);

    while(rev>0)
    {
        if(count % 2 != 0)
        {
            int digit = rev % 10;
            printf("%d\n",digit);
            sum = sum + digit;
       
        }
        rev = rev / 10;
        
        count++;
    }

    printf("The sum of %d natural number is %d\n", n, sum);
    return 0;
}    