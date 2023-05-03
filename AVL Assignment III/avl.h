typedef struct node
{
    char *data;
    int balanceFactor;
    struct node* parent, *left, *right;
} node;

typedef node* AVL;

void initAVL(AVL* t);
void insertNodeIntoAVL(AVL *t, char *data);
void inorder(AVL t);
void balanceTree(AVL *t, node* nn);
int height(AVL t);
void destroyTree(AVL *p);
node* adjustImbalance(AVL *t);
void updateBalanceFactor(AVL *t);
void removeNodeIterative(AVL *t, char *key);
int getBalanceFactor(node* n);
void LLRotation(AVL* t, node *A);
void LRRotation(AVL* t, node *A);
void RLRotation(AVL* t, node *A);
void RRRotation(AVL* t, node *A);
