#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define IS_CONNECTED 1
#define NOT_CONNECTED 2
#define HAS_PHONE 3
#define NUM_CHILDREN 2
#define HEIGHT 20
#define MAX_SIZE 2000000

typedef struct TreeNode
{
    long long int data;
    struct TreeNode *left;
    struct TreeNode *right;
} Treenode;

typedef struct TrieNode
{
    struct TrieNode *children[NUM_CHILDREN];
    long long int count;
} Trienode;

typedef struct Solution
{
    struct TrieNode *root;
} Solution;

Treenode *createNode(long long int data)
{
    Treenode *newNode = (Treenode *)malloc(sizeof(Treenode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Treenode *makeTree(long long int nodes[], long long int n)
{
    Treenode *root = createNode(nodes[0]);
    Treenode *q[n];
    long long int front = -1, rear = -1;
    bool isLeft = true;
    Treenode *cur = NULL;

    q[++rear] = root;
    for (long long int i = 1; i < n; i++)
    {
        Treenode *node = NULL;
        if (nodes[i] == 1)
        {
            node = (Treenode *)malloc(sizeof(Treenode));
            node->data = nodes[i];
            node->left = NULL;
            node->right = NULL;
            q[++rear] = node;
        }
        if (isLeft)
        {
            cur = q[++front];
            cur->left = node;
            isLeft = false;
        }
        else
        {
            cur->right = node;
            isLeft = true;
        }
    }
    return root;
}

long long int count = 0;
long long int minimumPhones(Treenode *root)
{
    if (root == NULL)
        return 1;

    long long int l = minimumPhones(root->left);
    long long int r = minimumPhones(root->right);

    if (l == IS_CONNECTED && r == IS_CONNECTED)
        return NOT_CONNECTED;

    else if (l == NOT_CONNECTED || r == NOT_CONNECTED)
    {
        count++;
        return HAS_PHONE;
    }

    else
        return IS_CONNECTED;
}

Trienode *createTrieNode()
{
    Trienode *node = (Trienode *)malloc(sizeof(Trienode));
    if (node)
    {
        node->count = 0;
        for (long long int i = 0; i < NUM_CHILDREN; ++i)
            node->children[i] = NULL;
    }
    return node;
}

Solution *createSolution()
{
    Solution *solution = (Solution *)malloc(sizeof(Solution));
    if (solution)
        solution->root = createTrieNode();

    return solution;
}

void insert(Solution *solution, long long int num)
{
    Trienode *node = solution->root;
    for (long long int i = HEIGHT; i >= 0; --i)
    {
        long long int bit = (num >> i) & 1;
        if (node->children[bit] == NULL)
            node->children[bit] = createTrieNode();

        node = node->children[bit];
        ++node->count;
    }
}

long long int getCount(Solution *solution, long long int num, long long int limit)
{
    long long int count = 0;
    Trienode *node = solution->root;
    for (long long int i = HEIGHT; i >= 0; --i)
    {
        long long int bit = (num >> i) & 1;
        long long int bitLimit = (limit >> i) & 1;
        if (bitLimit == 1)
        {
            if (node->children[bit] != NULL)
                count += node->children[bit]->count;
            node = node->children[bit ^ 1];
        }
        else
            node = node->children[bit];
        if (node == NULL)
            break;
    }
    return count;
}

long long int countPairs(long long int *arr, long long int size, long long int low, long long int high)
{
    long long int ans = 0;
    Solution *solution = createSolution();
    if (solution == NULL)
        return -1;
    for (long long int i = 0; i < size; ++i)
    {
        ans += getCount(solution, arr[i], high + 1) - getCount(solution, arr[i], low);
        insert(solution, arr[i]);
    }
    free(solution);
    return ans;
}

int main()
{
    long long int n;
    scanf("%lld", &n);

    long long int levelOrder[n];
    for (long long int i = 0; i < n; i++)
        scanf("%lld", &levelOrder[i]);

    long long int l, r;
    scanf("%lld %lld", &l, &r);
    if (n == 0)
    {
        printf("0\n0");
        return 0;
    }

    Treenode *root = makeTree(levelOrder, n);

    long long int m = minimumPhones(root);
    long long int ans = 0;
    if (m == NOT_CONNECTED)
    {
        printf("%lld\n", count + 1);
        ans = count + 1;
    }
    else
    {
        printf("%lld\n", count);
        ans = count;
    }

    long long int primeNumbers[MAX_SIZE + 1];
    bool prime[MAX_SIZE + 1];
    for (long long int i = 2; i <= 40 * ans; i++)
        prime[i] = true;

    for (long long int p = 2; p * p <= 40 * ans; p++)
    {
        if (prime[p] == true)
        {
            for (long long int i = p * p; i <= 40 * ans; i += p)
                prime[i] = false;
        }
    }

    long long int index = 0;
    for (long long int p = 2; index < ans; p++)
    {
        if (prime[p])
        {
            primeNumbers[index] = p;
            index++;
        }
    }

    long long int ans_1 = countPairs(primeNumbers, ans, l, r);
    ans_1 = ((ans * (ans - 1)) / 2) - ans_1;
    printf("%lld\n", ans_1);

    return 0;
}