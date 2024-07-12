#include <stdio.h>
#include <stdlib.h>

typedef struct Station
{
    int depth;
    int time;
    int refill;
} Station;

int comparator(const void *a, const void *b)
{
    return ((Station *)a)->depth - ((Station *)b)->depth;
}

void minimum_refill_time(int n, int k, int d, int p, Station *stations)
{
    qsort(stations, n, sizeof(Station), comparator);
    
    int *heap = (int *)malloc(sizeof(int) * n);
    int heap_size = 0;
    int current_depth = 0;
    int oxygen_supply = k;
    int total_time = 0;

    for (int i = 0; i < n; ++i)
    {
        int depth = stations[i].depth;
        int refill_time = stations[i].time;
        int refill_amount = stations[i].refill;

        while (current_depth < depth)
        {
            if (heap_size == 0)
            {
                printf("-1 %d\n", current_depth);
                free(heap);
                return;
            }
            int min_refill_time = heap[0];
            total_time += min_refill_time;
            oxygen_supply += p;
            current_depth += 1;
            // Heapify down
            int index = 0;
            while (1)
            {
                int child = 2 * index + 1;
                if (child >= heap_size)
                    break;

                if (child + 1 < heap_size && heap[child + 1] < heap[child])
                    child += 1;

                if (heap[child] < min_refill_time)
                {
                    heap[index] = heap[child];
                    index = child;
                }
                else
                    break;
            }
            heap[index] = min_refill_time;
        }
        if (oxygen_supply < 1)
        {
            printf("-1 %d\n", current_depth - 1);
            free(heap);
            return;
        }
        heap[heap_size++] = refill_time;
        // Heapify up
        int index = heap_size - 1;
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent])
            {
                // Swap
                int temp = heap[index];
                heap[index] = heap[parent];
                heap[parent] = temp;
                index = parent;
            }
            else
                break;
        }scanf("%d", &stations[i].refill);
    }

    while (current_depth < d)
    {
        if (heap_size == 0)
        {
            printf("-1 %d\n", current_depth);
            free(heap);
            return;
        }
        int min_refill_time = heap[0];
        total_time += min_refill_time;
        oxygen_supply += p;
        current_depth += 1;
        // Heapify down
        int index = 0;
        while (1)
        {
            int child = 2 * index + 1;
            if (child >= heap_size)
                break;

            if (child + 1 < heap_size && heap[child + 1] < heap[child])
                child += 1;

            if (heap[child] < min_refill_time)
            {
                heap[index] = heap[child];
                index = child;
            }
            else
                break;
        }
        heap[index] = min_refill_time;
    }
    printf("%d\n", total_time);
    free(heap);
}

int main()
{
    int n, k, d, p;
    scanf("%d %d %d %d", &n, &k, &d, &p);

    Station *stations = (Station *)malloc(sizeof(Station) * n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &stations[i].depth);
    for (int i = 0; i < n; ++i)
        scanf("%d", &stations[i].time);
    for (int i = 0; i < n; ++i)
        scanf("%d", &stations[i].refill);

    minimum_refill_time(n, k, d, p, stations);
    free(stations);

    return 0;
}