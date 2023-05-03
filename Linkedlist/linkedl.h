typedef struct node
{
    int data;
    struct node* next;
} node;

typedef node* List;

void initList(List *l);
void insertAtBeginning(List *l, int data);
void insertAtMiddle(List *l, int data, int position);
void insertAtEnd(List *l, int data);
int deleteFromBeginning(List *l);
int deleteFromMiddle(List *l, int position);
int deleteFromEnd(List *l);
int searchNode(List l, int data);
void traverse(List l);

