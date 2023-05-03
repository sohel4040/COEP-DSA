typedef struct node
{
    int data;
    struct node *left, *right;
} node;

typedef node* Tree;

void initTree(Tree *);
void insertNode(Tree *, int);
int searchAnElement(Tree, int);
node* removeNode(Tree *, int);
void inOrderTraversal(Tree);
void inOrderTraverseIterative(Tree);
void preOrderTraversal(Tree);
void postOrderTraversal(Tree);


