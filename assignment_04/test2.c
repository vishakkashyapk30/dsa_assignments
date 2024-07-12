#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10000

typedef struct Minheap
{
    int *arr;
    int capacity;
    int size;
} MinHeap;

MinHeap *createMinHeap()
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->arr = (int *)malloc(sizeof(int) * INITIAL_SIZE);
    heap->capacity = INITIAL_SIZE;
    heap->size = 0;
    return heap;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap *heap, int index)
{
    while (index > 0 && heap->arr[index] < heap->arr[(index - 1) / 2])
    {
        swap(&heap->arr[index], &heap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(MinHeap *heap, int index)
{
    int smallest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < heap->size && heap->arr[leftChild] < heap->arr[smallest])
        smallest = leftChild;

    if (rightChild < heap->size && heap->arr[rightChild] < heap->arr[smallest])
        smallest = rightChild;

    if (smallest != index)
    {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

void insert(MinHeap *heap, int value)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity *= 2;
        heap->arr = (int *)realloc(heap->arr, sizeof(int) * heap->capacity);
    }
    heap->arr[heap->size] = value;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

int extractMin(MinHeap *heap)
{
    if (heap->size == 0)
    {
        printf("Heap is empty\n");
        return -1;
    }
    int min = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return min;
}

void printHeap(MinHeap *heap)
{
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->arr[i]);
    printf("\n");
}

int main()
{
    MinHeap *heap = createMinHeap();
    insert(heap, 10);
    insert(heap, 20);
    insert(heap, 15);
    insert(heap, 40);
    insert(heap, 50);
    insert(heap, 100);
    insert(heap, 5);

    printHeap(heap);
    printf("Extracted min: %d\n", extractMin(heap));
    printHeap(heap);

    free(heap->arr);
    free(heap);
    return 0;
}
