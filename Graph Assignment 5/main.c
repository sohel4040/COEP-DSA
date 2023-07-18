#include<stdio.h>
#include"graph.h"
#include"queue.h"

int main(int argc, char **argv)
{
    Graph g;
    initGraph(&g, argv[1]);

    printf("Adjacency Matrix of a graph is: \n");
    displayGraph(g);
  
    int n = 1;
    printf("BFS traversal of a graph form starting node %d :\n", n);
    BFS(g, n);

    printf("DFS traversal of a graph from starting node %d :\n", n);
    DFS(g, 1);

    printf("Degree of each vertices is \n");
    displayDegreeOfVertices(g);

    printf("Graph is connected or not: \n");
    int x = isConnectedGraph(g);
    if(x == 1)
        printf("Graph is connected\n");
    else if(x == 0)
        printf("Graph is not connected\n");
    else 
        printf("Something went wrong\n");


    int count = countNumberOfComponents(g, 1);
    printf("Total Number of components in a graph is %d\n", count);


    int y = checkIfOneVertexIsAdjacentToAnother(g, 1, 3);

    if(y)
        printf("Adjacent\n");
    else
        printf("Not Adjacent\n");

    return 0;
}