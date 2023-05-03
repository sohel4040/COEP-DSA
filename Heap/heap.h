typedef struct Heap
{
    int *arr;
    int size;
} Heap;

void initHeap(Heap *t);
void insert(Heap *t, int data);
int deleteFromHeap(Heap *t);
void printArray(int *arr, int size);


