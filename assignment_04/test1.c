#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct data
{
    int depth;
    long long int time;
} data;

typedef struct stNode
{
    struct data station;
    int idx;
} node;

typedef struct stHeap
{
    struct node *heaparray;
    int capacity;
    int size;
} heap;

heap *createHeap(int capacity)
{
    heap *Heap = (heap *)malloc(sizeof(heap));
    Heap->heaparray = (node *)malloc(capacity * (sizeof(node)));
    Heap->capacity = capacity;
    Heap->size = 0;
    return Heap;
}

void swapNode(node* a, node* b)
{
    node temp = *a;
    *a = *b;
    *b = temp;
}



int compare(const void *a, const void *b)
{
    data *s1 = (data *)a;
    data *s2 = (data *)b;
    return s1->depth - s2->depth;
}

int main()
{
    int n, k, d, p;
    scanf("%d %d %d %d", &n, &k, &d, &p);

    data *stations = (data *)malloc(n * sizeof(data));
    for (int i = 0; i < n; i++)
        scanf("%d", &stations[i].depth);

    for (int i = 0; i < n; i++)
        scanf("%lld", &stations[i].time);

    qsort(stations, n, sizeof(data), compare);

    return 0;
}