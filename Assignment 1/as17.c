#include<stdio.h>

int main()
{        
    float t;
   
    printf("Enter the temprature in farhenheit\n");
    scanf("%f",&t);

    float area = (t-32)*5/9;
    
    printf("Temprature in celcius is  %1.3f\n",area);

    return 0;
}    