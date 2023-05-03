#include<stdio.h>
#include"stack.h"

// Sohel Shamshuddin Bargir - 142203002
int isPalindrome(stack *s,char *str,int size)
{
    if(isEmpty(*s))
        return -1;

    for(int i=0;i<size;i++)
    {
        char c = pop(s);
        if(str[i] != c)
            return 0;
    }

    return 1;
}
void pushStringOntoStack(stack *s,char *str,int size)
{
    for(int i=0;i<size;i++)
    {
        push(s,str[i]);
    }
}

void printReversed(stack *s, char *str, int size)
{
    for(int i=0;i<size;i++)
    {
        char c = pop(s);
        printf("%c",c);
    }
}

int main()
{
    char str[]="abba";
    int size = sizeof(str)/sizeof(char);
    stack s;
    initStack(&s,size-1);
    pushStringOntoStack(&s,str,size-1);
    if(isPalindrome(&s,str,size-1))
        printf("The string is palindrome\n");
    else
        printf("The string is not palindrome\n");

    printf("The orginal string is %s\n",str);
    pushStringOntoStack(&s,str,size-1);
    printf("The reversed string is ");
    printReversed(&s,str,size-1);

    return 0;
}