typedef struct queuenode{
	int data;
	struct queuenode *next;
}queuenode;

typedef struct queue{
	queuenode*front;
	queuenode*rear;
	int count;
}queue;

void initqueue(queue *Q);
int isEmptyQueue(queue Q);
void enqueue(queue *Q, int k);
int dequeue(queue *Q);