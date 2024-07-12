#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    int minreq;
    int change;
} node;

int comparatorAscending(const void *a, const void *b)
{
    return ((node *)a)->minreq - ((node *)b)->minreq;
}

int comparatorDescending(const void *a, const void *b)
{
    return ((node *)b)->minreq - ((node *)a)->minreq;
}

int solve(int n, int k, int x[], int y[])
{
    node nodearr[n], pluspart[n], minuspart[n];
    int countP = 0, countN = 0, oxygenLevel = k;
    for (int i = 0; i < n; i++)
    {
        nodearr[i].minreq = x[i];
        nodearr[i].change = y[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (nodearr[i].change > 0)
        {
            pluspart[countP].minreq = nodearr[i].minreq;
            pluspart[countP].change = nodearr[i].change;
            countP++;
        }
        else
        {
            minuspart[countN].minreq = nodearr[i].minreq;
            minuspart[countN].change = nodearr[i].change;
            countN++;
        }
    }
    qsort(pluspart, countP, sizeof(node), comparatorAscending);
    qsort(minuspart, countN, sizeof(node), comparatorDescending);
    for (int i = 0; i < countP; i++)
    {
        if (oxygenLevel < pluspart[i].minreq)
            return 0;
        oxygenLevel += pluspart[i].change;
    }
    for (int i = 0; i < countN; i++)
    {   
        if (oxygenLevel < minuspart[i].minreq)
            return 0;
        else if (oxygenLevel + minuspart[i].change >= 0)
            oxygenLevel += minuspart[i].change;
        else
            return 0;
    }
    return 1;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    int x[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    
    int y[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &y[i]);

    int result = solve(n, k, x, y);
    if (result == 0)
        printf("NO");
    else
        printf("YES");

    return 0;
}