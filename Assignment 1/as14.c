#include<stdio.h>

int main()
{        
    int s,da=0;
    printf("Enter basic salary of an employee\n");
    scanf("%d",&s);

    if(s>=10000 && s <=20000)
    {
         da = s*0.10;
         printf("DA is %d",da);
    }
    else if (s>=20000 && s <=50000)
    {
        da = s*0.15;
         printf("DA is %d",da);
    }
    else if (s>50000 && s <=100000)
    {
        da = s*0.20;
         printf("DA is %d",da);
    }
    else
    {
        printf("DA is not given");
    }
    
    return 0;
}    