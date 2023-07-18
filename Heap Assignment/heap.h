typedef struct Heap
{
    int *arr;
    int size;
    int rear;
} Heap;

// void initHeap(Heap *t, int size);
void initHeap(Heap *t);
void insert(Heap *t, int data);
int removeFromHeap(Heap *t);
void heapify(Heap *h);
void heapsort(Heap *h);
void traverse(Heap h);
int isEmptyHeap(Heap h);
int isFullHeap(Heap h);




