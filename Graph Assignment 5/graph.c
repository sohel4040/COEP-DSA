#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"graph.h"
#include"queue.h"
#include"stack.h"

void initGraph(Graph *g, char *filename)
{
    FILE* ptr;

    ptr = fopen("adjacency_matrix.txt", "r");

    if(!ptr)
        return;

    fscanf(ptr, "%d", &g->n);

    g->A = (int**) malloc(sizeof(int*)*g->n);

    if(!g->A)
        return;

    for(int i = 0; i < g->n; i++)
    {
        g->A[i] = (int*) malloc(sizeof(int)*g->n);

        if(!g->A[i])
        {
            for(int k = i-1; k >= 0; k--)
            {
                free(g->A[k]);
            }

            free(g->A);
            return;
        }

        for(int j = 0; j < g->n; j++)
        {
            fscanf(ptr, "%d", &(g->A[i][j]));
        }
    } 

    return;
}

void displayGraph(Graph g)
{
    if(!g.A)
        return;
    
    int n = g.n;
    for(int i = 0; i < n; i++)
    {
        if(g.A[i])
        {
            for(int j = 0; j < n; j++)
            {
                printf("%d ", g.A[i][j]);
            }
            printf("\n");
        }
    }
}

void BFS(Graph g, int start)
{
    int n = g.n;
    int *visited = (int*) calloc(n, sizeof(int));

    if(!visited)
        return;
    
    queue q;
    initqueue(&q);
    enqueue(&q, start);
    visited[start] = 1;

    int v;

    while(!isEmptyQueue(q))
    {
        v = dequeue(&q);
        printf("%d ", v);
        visited[v] = 1;

        for(int i = 0; i < n; i++)
        {
            if(g.A[v][i] && !visited[i])
            {
                enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }

    free(visited);
    printf("\n");
    return;
}

void DFS(Graph g, int start)
{
    int n = g.n;
    int *visited = (int*) calloc(n, sizeof(int));

    if(!visited)
        return;
    
    stack st;
    initstack(&st);
    push(&st, start);
    visited[start] = 1;

    int v;

    while(!isEmptyStack(st))
    {
        v = pop(&st);
        printf("%d ", v);

        visited[v] = 1;

        for(int i = 0; i < n; i++)
        {
            if(g.A[v][i] && !visited[i])
            {
                push(&st, i);
                visited[i] = 1;
            }
        }
    }

    printf("\n");
    free(visited);
    return;
}

void displayDegreeOfVertices(Graph g)
{
    if(!g.A)
        return;
    
    int n = g.n;
    for(int i = 0; i < n; i++)
    {
        if(g.A[i])
        {
            printf("Degree of %d: ", i);
            int count = 0;
            for(int j = 0; j < n; j++)
            {
                if(g.A[i][j])
                    count++;
                     
            }
            printf("%d\n", count);
        }
    }
}

int isConnectedGraph(Graph g)
{
    int start = 0;
    int n = g.n;
    int* visited = (int*) calloc(n, sizeof(int));

    if(!visited)
        return INT_MIN;

    queue q;
    initqueue(&q);
    enqueue(&q, start);
    visited[start] = 1;

    int v;

    while(!isEmptyQueue(q))
    {
        v = dequeue(&q);
        visited[v] = 1;
        for(int i = 0; i < n; i++)
        {
            if(g.A[v][i] && !visited[i])
            {
                enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        if(!visited[i])
        {
            free(visited);
            return 0;
        }
    }
    free(visited);
    return 1;
}

int countNumberOfComponents(Graph g, int start)
{
    int count = 0;
    queue q;
    initqueue(&q);
    int n = g.n;
    int* visited = (int*) calloc(n, sizeof(int));

    if(!visited)
        return 0;

    int numberOfVertices, j = 1;

    while(1)
    {
        numberOfVertices = 1;
        enqueue(&q, start);
        visited[start] = 1;
        int v;

        while(!isEmptyQueue(q))
        {
            v = dequeue(&q);
            visited[v] = 1;
            for(int i = 0; i < n; i++)
            {
                if(g.A[v][i] && !visited[i])
                {
                    enqueue(&q, i);
                    visited[i] = 1;
                    numberOfVertices++;
                }
            }
        }
        count++;
        
        int flag = 1;
        for(int i = 0; i < n; i++)
        {
            if(!visited[i])
            {
                flag = 0;
                start = i;
            }
        }

        printf("Number of vertices in Component %d: %d\n", j, numberOfVertices);
        j++;
        if(flag)
            break;
    }

    free(visited);
    return count;
}

int checkIfOneVertexIsAdjacentToAnother(Graph g, int u, int v)
{
    if(u > g.n || v > g.n)
        return INT_MIN;
        
    return (g.A[u][v] || g.A[v][u]);
}
