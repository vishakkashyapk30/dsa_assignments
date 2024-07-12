#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Connection
{
    int destination;
    int latency;
} Connection;

typedef struct Node
{
    int vertex;
    int distance;
    struct Node *next;
} Node;

typedef struct PriorityQueue
{
    Node *head;
} PriorityQueue;

void push(PriorityQueue *pq, int vertex, int distance)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->vertex = vertex;
    new_node->distance = distance;
    new_node->next = NULL;

    if (!pq->head || distance < pq->head->distance)
    {
        new_node->next = pq->head;
        pq->head = new_node;
    }
    else
    {
        Node *current = pq->head;
        while (current->next && current->next->distance < distance)
            current = current->next;
        new_node->next = current->next;
        current->next = new_node;
    }
}

Node *pop(PriorityQueue *pq)
{
    if (!pq->head)
        return NULL;
    Node *temp = pq->head;
    pq->head = pq->head->next;
    return temp;
}

int *dijkstra(int n, Connection **graph, int *graph_sizes)
{
    int *distances = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++)
        distances[i] = INT_MAX;

    PriorityQueue pq = {NULL};
    distances[1] = 0;
    push(&pq, 1, 0);

    while (pq.head)
    {
        Node *top = pop(&pq);
        int u = top->vertex;
        int dist_u = top->distance;
        free(top);

        if (distances[u] < dist_u)
            continue;

        for (int i = 0; i < graph_sizes[u]; i++)
        {
            Connection edge = graph[u][i];
            int v = edge.destination;
            int weight = edge.latency;
            if (distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                push(&pq, v, distances[v]);
            }
        }
    }
    return distances;
}

int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    Connection **graph = (Connection **)malloc((n + 1) * sizeof(Connection *));
    int *graph_sizes = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++)
    {
        graph[i] = NULL;
        graph_sizes[i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        graph[a] = (Connection *)realloc(graph[a], (graph_sizes[a] + 1) * sizeof(Connection));
        graph[a][graph_sizes[a]++] = (Connection){b, l};
        graph[b] = (Connection *)realloc(graph[b], (graph_sizes[b] + 1) * sizeof(Connection));
        graph[b][graph_sizes[b]++] = (Connection){a, l};
    }

    Connection *direct_connections = NULL;
    int direct_connections_size = 0;

    for (int i = 0; i < k; i++)
    {
        int c, p;
        scanf("%d %d", &c, &p);
        graph[1] = (Connection *)realloc(graph[1], (graph_sizes[1] + 1) * sizeof(Connection));
        graph[1][graph_sizes[1]++] = (Connection){c, p};
        graph[c] = (Connection *)realloc(graph[c], (graph_sizes[c] + 1) * sizeof(Connection));
        graph[c][graph_sizes[c]++] = (Connection){1, p};
        direct_connections = (Connection *)realloc(direct_connections, (direct_connections_size + 1) * sizeof(Connection));
        direct_connections[direct_connections_size++] = (Connection){c, p};
    }

    int *distances = dijkstra(n, graph, graph_sizes);

    int max_removed = 0;
    for (int i = 0; i < direct_connections_size; i++)
    {
        Connection connection = direct_connections[i];
        int c = connection.destination;
        int p = connection.latency;
        if (p > distances[c])
            max_removed++;
    }
    
    printf("%d\n", max_removed);

    return 0;
}