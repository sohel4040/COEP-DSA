#include<stdio.h>
#include"graph.h"

int main(int argc, char **argv)
{
    Graph g;
    initGraph(&g, argv[1]);

    // printf("Adjacency List of input graph is : \n");
    // display(g);

    // printf("BFS Traversal of graph is : \n");
    // BFS(g, 'a');

    // printf("DFS Traversal of graph is : \n");
    // DFS(g, 'a');

    printf("Minimum Spanning Tree of a graph using Kruskal's Algorithm is : \n");
    // MST s = minimumSpanningTreeUsingPrimsAlgorithm(g, 'a');
    MST s = minimumSpanningTreeUsingkruskalsAlgorithm(g);
    
    mst *t = s;

    while(t)
    {
        printf("%c -> %c\n", t->from, t->to);
        t = t->next;
    }
    printf("\n");
    
  
    return 0;
}