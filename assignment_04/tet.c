#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000
#define min(a, b) ((a) < (b) ? (a) : (b))

struct Station
{
    int depth;
    int time;
};

struct MinHeap
{
    struct Station *array;
    int capacity;
    int size;
};

void swapStation(struct Station *a, struct Station *b)
{
    struct Station t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].time < minHeap->array[smallest].time)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].time < minHeap->array[smallest].time)
        smallest = right;
    
    if (smallest != idx)
    {
        swapStation(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (struct Station *)malloc(capacity * sizeof(struct Station));
    return minHeap;
}

void insertMinHeap(struct MinHeap *minHeap, struct Station station)
{
    if (minHeap->size == minHeap->capacity)
    {
        printf("Heap capacity exceeded\n");
        return;
    }
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i] = station;

    while (i && minHeap->array[(i - 1) / 2].time > minHeap->array[i].time)
    {
        swapStation(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

struct Station extractMin(struct MinHeap *minHeap)
{
    struct Station temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

int compareDepth(const void *a, const void *b)
{
    struct Station *s1 = (struct Station *)a;
    struct Station *s2 = (struct Station *)b;
    return s1->depth - s2->depth;
}

int minTotalTime(struct Station stations[], int n, int k, int d, int p)
{
    struct MinHeap *minHeap = createMinHeap(n);

    int curDepth = 0, totalTime = 0, windowStart = 0;
    for (int windowEnd = 0; windowEnd < n; windowEnd++)
    {
        // Insert stations in the window into the min heap
        while (windowEnd < n && stations[windowEnd].depth - curDepth <= k)
        {
            insertMinHeap(minHeap, stations[windowEnd]);
            windowEnd++;
        }

        // Refill oxygen at stations as needed
        while (windowEnd < n && stations[windowEnd].depth - curDepth > k)
        {
            while (minHeap->size && stations[windowEnd].depth - curDepth > k)
            {
                struct Station minStation = extractMin(minHeap);
                int refill = min((stations[windowEnd].depth - curDepth + p - 1) / p, minStation.time);
                curDepth += refill * p;
                totalTime += refill;
                minStation.time -= refill;
                if (minStation.time > 0)
                    insertMinHeap(minHeap, minStation);
            }
            if (stations[windowEnd].depth - curDepth > k)
                return -1; // Percy cannot reach the next station
        }
        windowStart = windowEnd;
    }

    // Refill oxygen at stations as needed to reach the final depth
    while (d - curDepth > k)
    {
        if (!minHeap->size)
            return -1; // Percy cannot reach the final depth
        struct Station minStation = extractMin(minHeap);
        int refill = min((d - curDepth + p - 1) / p, minStation.time);
        curDepth += refill * p;
        totalTime += refill;
        minStation.time -= refill;
        if (minStation.time > 0)
            insertMinHeap(minHeap, minStation);
    }

    free(minHeap->array);
    free(minHeap);

    return totalTime;
}

int main()
{
    int n, k, d, p;
    scanf("%d %d %d %d", &n, &k, &d, &p);

    struct Station *stations = (struct Station *)malloc(n * sizeof(struct Station));
    if (stations == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
        scanf("%d", &stations[i].depth);
    for (int i = 0; i < n; i++)
        scanf("%d", &stations[i].time);

    qsort(stations, n, sizeof(struct Station), compareDepth);

    int minTime = minTotalTime(stations, n, k, d, p);
    if (minTime == -1)
    {
        printf("-1 ");
        int maxDepth = 0;
        for (int i = 0; i < n; i++)
        {
            if (stations[i].depth <= k && stations[i].depth > maxDepth)
                maxDepth = stations[i].depth;
            
        }
        printf("%d\n", maxDepth);
    }
    else
        printf("%d\n", minTime);
    
    free(stations);

    return 0;
}