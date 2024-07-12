#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define isConnected 1
#define notConnected 2
#define hasPhone 3

struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode Treenode;

Treenode *createNode(int data)
{
    Treenode *newNode = (Treenode *)malloc(sizeof(Treenode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Treenode *makeTree(int nodes[], int n)
{
    Treenode *root = createNode(nodes[0]);
    Treenode *q[n];
    int front = -1, rear = -1;
    bool isLeft = true;
    Treenode *cur = NULL;
    q[++rear] = root;
    for (int i = 1; i < n; i++)
    {
        struct TreeNode *node = NULL;
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

int count = 0;
int minimumPhones(Treenode *root)
{
    if (root == NULL)
        return 1;

    int l = minimumPhones(root->left);
    int r = minimumPhones(root->right);

    if (l == isConnected && r == isConnected)
        return notConnected;

    else if (l == notConnected || r == notConnected)
    {
        count++;
        return hasPhone;
    }

    else
        return isConnected;
}

int main()
{
    int n;
    scanf("%d", &n);

    int levelOrder[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &levelOrder[i]);

    Treenode *root = makeTree(levelOrder, n);
    
    if (minimumPhones(root) == notConnected) 
        printf("%d", count + 1);
    else
        printf("%d", count);

    return 0;
}