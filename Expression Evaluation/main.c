#include<stdio.h>
#include"stack.h"
#include<limits.h>
#include<stdlib.h>



void convertInfixToPostfix(stack *s, char *infix, char *postfix, int size)
{
    int index = 0;
    for(int i=0;i<size;i++)
    {
        char c = infix[i];
        
        char p = peek(*s);
        if(((c == '+' || c == '-') && (p == '*' || p == '/' || p == '-' || p == '+') ) || ((c == '*' || c == '/') && (p == '*' || p == '/' ) ))
        {
            char n = pop(s);
            p = peek(*s);
            postfix[index++] = n;

            if(((c == '+' || c == '-') && (p == '*' || p == '/' || p == '-' || p == '+') ) || ((c == '*' || c == '/') && (p == '*' || p == '/' ) ))
            {
                char n = pop(s);
                postfix[index++] = n;
            }
            push(s,c);
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(')
        {
            push(s, c);
        }
        else if(c >= '0' && c <= '9' )
        {
            postfix[index++] = c;
        }
        if( c == ')')
        {
            char p = pop(s);
            while( p != '(' && !isEmpty(*s))
            {
                postfix[index++]=p;
                p = pop(s);
            }
        }
    }
    
    while(!isEmpty(*s))
    {
        postfix[index++] = pop(s);
    }
}

int evaluatePostfix(stack *s, char *postfix, int size)
{
    int eval=0;
    for(int i=0;i<size;i++)
    {
        char c = postfix[i];
       
        if(!(c == '+' || c == '-' || c == '*' || c == '/'))
        {
            push(s,c);
        }
        else 
        {
            int b = pop(s) - '0';
            int a = pop(s) - '0';
            switch(c)
            {
                case '+': 
                        eval = a+b;
                        break;
                case '-':
                        eval = a-b;
                        break;
                case '*':
                        eval = a*b;
                        break;
                case '/':
                        eval = a/b;
                        break;
            }
            push(s,eval + '0');
        }
    }

    return eval;
}

void printExpression(char *expr, int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%c",expr[i]);
    }
}

int main()
{
    char infix[]="3*3/1+2*(2+1*4/1)";
    // 2*4+5-3*(2/2*3)/3+5*2-1/2
    int size = sizeof(infix) / sizeof(char);
    stack s;
    initStack(&s,size);
    char *postfix = (char*) malloc(sizeof(char)*size);

    convertInfixToPostfix(&s, infix, postfix, size);

    printExpression(postfix,size);

    printf("\nResult of postfix expression is %d\n",evaluatePostfix(&s,postfix, size-1));



    return 0;
}
