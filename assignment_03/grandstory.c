#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ARRAY_SIZE 200002
#define HASH_SIZE 200003

typedef struct Node
{
    int key;
    int value;
    int index;
    struct Node *next;
} Node;

typedef struct HashTable
{
    Node *head[HASH_SIZE];
} HashTable;

Node *createNode(int key, int value, int index)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
        return newNode;
    newNode->key = key;
    newNode->value = value;
    newNode->index = index;
    newNode->next = NULL;
    return newNode;
}

void initHashTable(HashTable *hashTable)
{
    for (int i = 0; i < HASH_SIZE; i++)
        hashTable->head[i] = NULL;
}

int hashFunction(int key)
{
    return abs(key) % HASH_SIZE;
}

void insert(HashTable *hashTable, int key, int value, int index)
{
    int hash = hashFunction(key);
    Node *newNode = createNode(key, value, index);
    if (hashTable->head[hash] == NULL)
        hashTable->head[hash] = newNode;
    else
    {
        newNode->next = hashTable->head[hash];
        hashTable->head[hash] = newNode;
    }
}

Node *search(HashTable *hashTable, int key)
{
    int hashIndex = hashFunction(key);
    Node *temp = hashTable->head[hashIndex];
    while (temp != NULL)
    {
        if (temp->key == key)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void solve(HashTable *hashTable, int n, int *book)
{
    int max_length = 0;
    int start_index = 0;
    Node *start_node = NULL;

    for (int i = 0; i < n; i++)
    {
        int length = 1;
        int prev_element = book[i] - 1;
        Node *node = search(hashTable, prev_element);

        if (node != NULL)
            length = node->value + 1;

        insert(hashTable, book[i], length, i);

        if (length > max_length)
        {
            max_length = length;
            start_index = book[i] - max_length + 1;
            start_node = search(hashTable, start_index);
        }
    }
    printf("%d\n", max_length);
    Node *current_node = start_node;
    for (int i = 0; i < max_length; i++)
    {
        printf("%d ", current_node->index);
        current_node = search(hashTable, current_node->key + 1);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    int *book = (int *)malloc(HASH_SIZE * sizeof(int *));
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    initHashTable(hashTable);

    for (int i = 0; i < n; i++)
        scanf("%d", &book[i]);

    solve(hashTable, n, book);

    for (int i = 0; i < HASH_SIZE; i++)
    {
        Node *current = hashTable->head[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    return 0;
}