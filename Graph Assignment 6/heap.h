typedef struct edge
{
    char from, to;
    int weight;
} edge;

typedef struct Heap
{
    edge **arr;
    int size;
    int rear;
} Heap;

// void initHeap(Heap *t, int size);
void initHeap(Heap *t);
void insert(Heap *t, edge *e);
edge* removeFromHeap(Heap *t);
void heapify(Heap *h);
int isEmptyHeap(Heap h);
int isFullHeap(Heap h);
void traverse(Heap h);




