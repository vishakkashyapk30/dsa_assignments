#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct graphNode
{
    int v;
    struct graphNode *next;
} graphnode;

typedef struct graph
{
    int numVertices;
    struct graphNode **adjLists;
} graph;

typedef struct stack
{
    int top;
    int *array;
    int maxSize;
} stack;

stack *createStack(int maxSize)
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = -1;
    s->maxSize = maxSize;
    s->array = (int *)malloc(maxSize * sizeof(int));
    return s;
}

bool isStackEmpty(stack *s)
{
    return s->top == -1;
}

void push(stack *s, int item)
{
    if (s->top == s->maxSize - 1)
    {
        s->maxSize *= 2;
        s->array = (int *)realloc(s->array, s->maxSize * sizeof(int));
    }
    s->array[++s->top] = item;
}

int pop(stack *s)
{
    if (isStackEmpty(s))
        return -1;
    return s->array[s->top--];
}

graphnode *createGraphNode(int vertex)
{
    graphnode *newNode = (graphnode *)malloc(sizeof(graphnode));
    if (newNode == NULL)
        return NULL;
    newNode->v = vertex;
    newNode->next = NULL;
    return newNode;
}

graph *createGraph(int n)
{
    graph *g = (graph *)malloc(sizeof(graph));
    if (g == NULL)
        return NULL;
    g->numVertices = n + 1;
    g->adjLists = (graphnode **)calloc(g->numVertices, sizeof(graphnode *));
    if (g->adjLists == NULL)
        return NULL;
    return g;
}

void addEdge(graph *g, int v1, int v2)
{
    graphnode *newNode = createGraphNode(v2);
    newNode->next = g->adjLists[v1];
    g->adjLists[v1] = newNode;
    newNode = createGraphNode(v1);
    newNode->next = g->adjLists[v2];
    g->adjLists[v2] = newNode;
}

void dfs(graph *g, int v, int visited[])
{
    stack *s = createStack(g->numVertices);
    push(s, v);

    while (!isStackEmpty(s))
    {
        int currentVertex = pop(s);
        visited[currentVertex] = 1;

        graphnode *var = g->adjLists[currentVertex];
        while (var)
        {
            int adjVertex = var->v;
            if (!visited[adjVertex])
                push(s, adjVertex);
            var = var->next;
        }
    }
    free(s->array);
    free(s);
}

void solve(graph *g, int n)
{
    int *visited = (int *)calloc(g->numVertices, sizeof(int));
    if (visited == NULL)
        return;
    int *connectedVertices = (int *)malloc(g->numVertices * sizeof(int));
    if (connectedVertices == NULL)
        return;
    int size = 0, count = 0;
    for (int i = 1; i < g->numVertices; i++)
    {
        if (visited[i] == 0)
        {
            connectedVertices[size++] = i;
            count++;
            dfs(g, i, visited);
        }
    }
    printf("%d\n", count - 1);
    if (count > 1)
    {
        for (int i = 0; i < count - 1; i++)
            printf("%d %d\n", connectedVertices[i], connectedVertices[i + 1]);
    }
    free(visited);
    free(connectedVertices);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    graph *g = createGraph(n);

    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(g, a, b);
    }

    solve(g, n);

    for (int i = 0; i < g->numVertices; i++)
    {
        graphnode *node = g->adjLists[i];
        while (node)
        {
            graphnode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    
    free(g->adjLists);
    free(g);

    return 0;
}