typedef struct node
{
    char data;
    int weight;
    struct node* next;
} node;

typedef node* List;

typedef struct mst
{
    char from, to;
    int weight;
    struct mst* next;
} mst;

typedef mst* MST;

typedef struct AdjacencyList
{
    List *list;
} AdjacencyList;

typedef struct Graph
{
    AdjacencyList *adjList;
    int vertices;
} Graph;

void initGraph(Graph *g, char* filename);
void DFS(Graph g, char start);
void BFS(Graph g, char start);
MST minimumSpanningTreeUsingPrimsAlgorithm(Graph g, char start);
MST minimumSpanningTreeUsingkruskalsAlgorithm(Graph g);
void display(Graph g);

void initMST(MST *l);
void append(MST *l, char from, char to, int weight);