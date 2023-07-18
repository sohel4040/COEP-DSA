#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include"queue.h"
#include"heap.h"
#include"graph.h"

void initGraph(Graph *g, char* filename)
{
    FILE* ptr;

    ptr = fopen(filename, "r");

    if(!ptr)
        return;

    fscanf(ptr, "%d", &g->vertices);

    g->adjList = (AdjacencyList*) malloc(sizeof(AdjacencyList));
    
    if(!g->adjList)
        return;
    
    List *list = (List*) malloc(sizeof(List)*g->vertices);

    if(!list)
        return;

    g->adjList->list = list;

    int data;
    for(int i = 0; i < g->vertices; i++)
    {
        for(int j = 0; j < g->vertices; j++)
        {
            fscanf(ptr, "%d", &data);
            if(data)
            {
                node* newnode =(node*) malloc(sizeof(node));
                if(!newnode)
                    return;
                newnode->data = 'a' + j;
                newnode->weight = data;
                newnode->next = NULL;


                if(!g->adjList->list[i])
                {
                    g->adjList->list[i] = newnode;
                }
                else
                {
                    newnode->next = g->adjList->list[i];
                    g->adjList->list[i] = newnode;
                }

            }
        }
    } 
    return;
}

void DFS(Graph g, char start)
{
    int startVertex = start - 'a';
    int n = g.vertices;
    int *visited = (int*) calloc(n, sizeof(int));

    if(!visited)
        return;
    
    stack st;
    initstack(&st);
    push(&st, startVertex);
    visited[startVertex] = 1;

    int v;

    while(!isEmptyStack(st))
    {
        v = pop(&st);
        printf("%c ", v + 'a');

        visited[v] = 1;

        node* temp = g.adjList->list[v];

        while(temp)
        {
            int data = temp->data - 'a';
            if(!visited[data])
            {
                push(&st, data);
                visited[data] = 1;
            }
            temp = temp->next;
        }

    }

    printf("\n");
    free(visited);
    return;
}

void BFS(Graph g, char start)
{
    int startVertex = start - 'a';
    int n = g.vertices;
    int *visited = (int*) calloc(n, sizeof(int));

    if(!visited)
        return;
    
    queue q;
    initqueue(&q);
    enqueue(&q, startVertex);
    visited[startVertex] = 1;

    int v;

    while(!isEmptyQueue(q))
    {
        v = dequeue(&q);
        printf("%c ", v + 'a');

        visited[v] = 1;

        node* temp = g.adjList->list[v];

        while(temp)
        {
            int data = temp->data - 'a';
            if(!visited[data])
            {
                enqueue(&q, data);
                visited[data] = 1;
            }
            temp = temp->next;
        }

    }

    printf("\n");
    free(visited);
    return;
}

void initMST(MST *l)
{
    *l = NULL;
    return;
}

void append(MST *l, char from, char to, int weight)
{
    mst *nn = (mst*) malloc(sizeof(node));
    nn -> from = from;
    nn -> to = to;
    nn -> weight = weight;
    nn -> next = NULL;

    if(!nn)
        return;

    if(!(*l))
    {
        *l = nn;
        return;
    }

    mst *temp = *l;
    while(temp->next)
    {
        temp = temp -> next;
    }

    temp -> next = nn;
    return;
}



MST minimumSpanningTreeUsingPrimsAlgorithm(Graph g, char start)
{
    int sum = 0;
    int startVertex = start - 'a';

    int n = g.vertices;
    int* visited = (int*) calloc(n, sizeof(int));

    if(!visited)
        return NULL;

    MST t;
    initMST(&t);

    Heap h;
    initHeap(&h);

    visited[startVertex] = 1;

    int v = startVertex;
    int edges = 0;

    while(1)
    {
        node* temp = g.adjList->list[v];

        while(temp)
        {
            int data = temp->data - 'a';
            if(!visited[data])
            {
                edge* e = (edge*) malloc(sizeof(edge));
                e->from = 'a' + v;
                e->to = 'a' + data;
                e->weight = temp->weight;
                insert(&h, e);
            }
            temp = temp->next;
        }
        edge *e = removeFromHeap(&h);
        int toNode = e->to - 'a';
        while(visited[toNode])
        {
            e = removeFromHeap(&h);
            if(!e)
                break;
            toNode = e->to - 'a';
        }
        if(isEmptyHeap(h))
            break;
        sum += e->weight;
        append(&t, e->from, e->to, e->weight);
        visited[toNode] = 1;
        v = toNode;

    }

    printf("%d\n", sum);
    free(visited);
    return t;
}


void display(Graph g)
{
    int n = g.vertices;

    for(int i = 0; i < n; i++)
    {
        printf("%c -> ", 'a' + i);
        node* temp = g.adjList->list[i];

        while(temp)
        {
            printf("%c ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

MST minimumSpanningTreeUsingkruskalsAlgorithm(Graph g)
{
    int sum = 0;

    int n = g.vertices;
    int* disjointSet = (int*) calloc(n, sizeof(int));

    if(!disjointSet)
        return NULL;

    for(int i=0; i < n; i++)
    {
        disjointSet[i] = i;
    }

    MST t;
    initMST(&t);

    Heap h;
    initHeap(&h);

    for(int i=0; i < n; i++)
    {
        node* temp = g.adjList->list[i];

        while(temp)
        {
            edge *e = (edge*) malloc(sizeof(edge));
            e->from = i + 'a';
            e->to = temp->data;
            e->weight = temp->weight;
            insert(&h, e);
            temp = temp->next;
        }
    }

    while(!isEmptyHeap(h))
    {
        edge *e = removeFromHeap(&h);
        int from = e->from - 'a';
        int to = e->to - 'a';

        if(disjointSet[from] != disjointSet[to])
        {
            int parent = disjointSet[to];
            for(int i=0; i < n; i++)
            {   
                if(disjointSet[i] == parent)
                {
                    disjointSet[i] = disjointSet[from];
                }
            }

            sum += e->weight;
            append(&t, e->from, e->to, e->weight);
        }
        
    }
    free(disjointSet);
    printf("%d\n", sum);
    return t;

}