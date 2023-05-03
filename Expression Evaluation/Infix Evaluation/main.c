#include<stdio.h>
#include"stack.h"

int checkifOperatorOrOperand(char c)
{
    int digit = c - '0';
    if(digit >= 0 && digit <=9)
        return 1;

    if(c == '+' || c == '-' || c == '*' || c == '/')
        return 2;
}

int checkPrecedence(char c)
{
    if(c == '*' || c == '/')
        return 2;

    if(c == '+' || c == '-')
        return 1;
    
}

void evaluate(stack *s, char ch, int a, int b)
{
    int res = 0; 
    switch(ch)
    {
        case '+': res = a + b;
                    break;

        case '-': res = a - b;
                    break;

        case '*': res = a * b;
                    break;

        case '/': res = a / b;
                    break;
    }
    push(s,res);

    return;

}

void pushOntoStack(stack *s1, stack *s2, char expr[], int size)
{
    
    for(int i=0; i< size ; i++)
    {
        char ch = expr[i];
        if(checkifOperatorOrOperand(ch) == 2 || ch == '(')
        {
            if(!isEmpty(*s2))
            {
                if(checkPrecedence(top(*s2)) > checkPrecedence(ch))
                {
                    int b = pop(s1) - '0';
                    int a = pop(s1) - '0'; 

                    char ch = pop(s2);
                    printf("%c",ch);
                    
                    evaluate(s1,ch,a,b);
                }
            }
            push(s2,ch);
        }
        else if(checkifOperatorOrOperand(ch) == 1)
        {
            push(s1,ch);
        }
        else if(ch == ')')
        {
           while(top(*s2) != '(')
           {

                int b = pop(s1) - '0';
                int a = pop(s1) - '0'; 

                char ch = pop(s2);
                printf("%c",ch);


                evaluate(s1,ch,a,b);
           }

           pop(s2);
        }

    }

    return;
}

int main()
{
    stack s1,s2;
    initstack(&s1);
    initstack(&s2);

    char expr[] = "2-3/5";
    int size = sizeof(expr) / sizeof(char);
    printf("%d",size);
    pushOntoStack(&s1,&s2,expr,size-1);
    printf("%d\n",pop(&s1));
    return 0;
}