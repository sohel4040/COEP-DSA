
typedef struct snode
{
    int data;
    struct snode * next;    
} snode;


typedef struct stack
{
    struct snode* top;
} stack;

void initstack(stack *s);
void push(stack *s, int data);
int pop(stack *s);
int isEmpty(stack s);
int top(stack s);
void display(stack s);





