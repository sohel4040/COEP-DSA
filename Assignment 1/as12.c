#include<stdio.h>

int main()
{        
    int a,b,c;
    printf("Enter three numbers\n");
    scanf("%d %d %d",&a,&b,&c);
    int ans=a>b ? (a>c ? a : c) : (b>c ? b : c);
    printf("Greater number among three number is %d\n",ans);
    return 0;
}    