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
    struct stNode *heaparray;
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

void swapNode(node *a, node *b)
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

void heapifyDown(heap *Heap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < Heap->size && Heap->heaparray[left].station.time < Heap->heaparray[smallest].station.time)
        smallest = left;

    if (right < Heap->size && Heap->heaparray[right].station.time < Heap->heaparray[smallest].station.time)
        smallest = right;

    if (smallest != idx)
    {
        swapNode(&Heap->heaparray[smallest], &Heap->heaparray[idx]);
        heapifyDown(Heap, smallest);
    }
}

void insertHeap(heap *Heap, node new_node)
{
    if (Heap->size == Heap->capacity)
        return;

    Heap->heaparray[Heap->size] = new_node;
    int i = Heap->size++;

    while (i != 0 && Heap->heaparray[(i - 1) / 2].station.time > Heap->heaparray[i].station.time)
    {
        swapNode(&Heap->heaparray[i], &Heap->heaparray[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

node extractMin(heap *Heap)
{
    if (Heap->size <= 0)
    {
        node emptyNode;
        emptyNode.station.time = -1;
        return emptyNode;
    }
    node root = Heap->heaparray[0];
    Heap->heaparray[0] = Heap->heaparray[Heap->size - 1];
    Heap->size--;
    heapifyDown(Heap, 0);

    return root;
}

void solve(int n, int k, int d, int p, data *stations, heap *Heap)
{
    long long int currentTime = 0;
    int i = 0;
    while (k < d)
    {
        while (i < n && stations[i].depth <= k)
        {
            node newNode;
            newNode.station = stations[i];
            newNode.idx = i;
            insertHeap(Heap, newNode);
            i++;
        }
        if (Heap->size == 0)
            break;

        node minNode = extractMin(Heap);
        currentTime += minNode.station.time;
        k += p;
    }
    if (k < d)
        printf("-1 %d\n", k);
    else
        printf("%lld\n", currentTime);
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

    heap *Heap = createHeap(n + 5);
    solve(n, k, d, p, stations, Heap);

    return 0;
}