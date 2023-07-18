typedef struct node{
	int data;
	struct node *next;
}node;

typedef struct queue{
	node*front;
	node*rear;
	int count;
}queue;

void initqueue(queue *Q);
int isEmptyQueue(queue Q);
void enqueue(queue *Q, int k);
int dequeue(queue *Q);