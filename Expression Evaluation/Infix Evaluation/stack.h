typedef struct node 
{
    int data;
    struct node * next;    
} node;


typedef struct stack
{
    struct node* top;
} stack;

void initstack(stack *s);
void push(stack *s,int data);
int pop(stack *s);
int isEmpty(stack s);
int top(stack s);
void display(stack s);





