typedef struct aBST
{
    int *array, size;
} aBST;

void initABST(aBST *t);
void insertNodeIntoABST(aBST *t, int key);
int heightOfTree(aBST t);
int countLeafNodes(aBST t);
int isComplete(aBST t);
void levelOrderTraversal(aBST t);
void inOrder(aBST t, int p);