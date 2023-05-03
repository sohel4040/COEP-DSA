#include<stdio.h>
#include"stack.c"

// Infix to postfix evaluation pending...
int precedence(char ch)
{
    if(ch == '+' || ch == '-')
        return 1;

    if(ch == '*' || ch == '/')
        return 2;

    return -1;
}

int isOperand(char ch)
{
    return ch >= '0' && ch <= '9';
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Infix to postfix conversion works
void convertInfixToPostfix(stack *s, char *infix, char *postfix, int size)
{
    int index = 0;
    for(int i=0;i<size;i++)
    {
        char ch = infix[i];

        if(isOperand(ch))
        {
            postfix[index++] = ch;    
        }
        else if(isOperator(ch))
        {
            while(!isEmpty(*s) && precedence(peek(*s)) >= precedence(ch))
            {
                postfix[index++] = pop(s);
            }
            push(s, ch);
        }
        else if(ch == ')')
        {
            while(!isEmpty(*s) && !(peek(*s) == '('))
            {
                postfix[index++] = pop(s);
            }
            pop(s);
        }
        else 
            push(s, ch);
       
    }
    
    while(!isEmpty(*s))
    {
        postfix[index++] = pop(s);
    }
    postfix[index] = '\0';
}

// need to be checked
int evaluatePostfix(stack *s, char *postfix, int size)
{
    int eval=0;
    printExpression(postfix,size);

    for(int i=0;i<size;i++)
    {
        char c = postfix[i];
       
        if(isOperand(c))
        {
            push(s,c);
        }
        else 
        {
            int b = pop(s) - '0';
            int a = pop(s) - '0';
            // printf("\n %d", a);
            // printf(" %d\n ", b);
            // printf("\n%c\n",c);
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

int main()
{
    char infix[]="2*4+5-3*(2/2*3)/3+5*2-1/2";
    // 3*3/1+2*(2+1*4/1)
    // 2*4+5-3*(2/2*3)/3+5*2-1/2
    int size = sizeof(infix) / sizeof(char);
    stack s;
    initStack(&s,size);
    char *postfix = (char*) malloc(sizeof(char)*size);

    convertInfixToPostfix(&s, infix, postfix, size);

    printf("\nResult of postfix expression is %d\n",evaluatePostfix(&s,postfix, size));

// 24*5+322/3**3/-52*+12/-

    return 0;
}