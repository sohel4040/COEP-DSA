#include<stdio.h>

int main()
{        
    float r;
    const float PI=3.14;
    printf("Enter the radius of a circle\n");
    scanf("%f",&r);

    double area = PI * r * r;
    double circum = 2 * PI * r ;
    
    printf("Area of a circle is %1.3f\n",area);
    printf("Circumference of a circle is %1.3f\n",area);

    return 0;
}    