    typedef struct stack
    {
        char *A;
        int n;
        int top;
    } stack;

    void initStack(stack *s,int n);
    int isFull(stack s);
    int isEmpty(stack s);
    void push(stack *s,char c);
    int pop(stack *s);