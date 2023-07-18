typedef struct Graph
{
    int **A;
    int n;
} Graph;

void initGraph(Graph *g, char *filename);
void displayGraph(Graph g);
void BFS(Graph g, int start);
void DFS(Graph G, int s);
void displayDegreeOfVertices(Graph g);
int isConnectedGraph(Graph g);
int countNumberOfComponents(Graph g, int start);
int checkIfOneVertexIsAdjacentToAnother(Graph g, int u, int v);