typedef struct node
{
    int data;
    struct node* next;
} node;

typedef struct queue
{
    struct node* front;
    struct node* rear;
} queue;

void initqueue(queue *q);
int isEmpty(queue q);
void enqueue(queue *q, int data);
int dequeue(queue *q);
void display(queue *q);