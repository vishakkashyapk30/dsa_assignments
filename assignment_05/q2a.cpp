#include <bits/stdc++.h>
using namespace std;

const long long int INF = LLONG_MAX;

typedef struct node
{
    long long int vertex;
    long long int cost;
    vector<int> fiberIndices;
} node;

void solve(int n, vector<vector<node>> &graphAdj, vector<pair<long long int, long long int>> &fibers)
{
    vector<long long int> distance(n + 1, INF);
    vector<int> fiberUsedToReach(n + 1, -1);
    vector<bool> fiberUsed(fibers.size(), false);
    distance[1] = 0;
    vector<pair<long long int, long long int>> heap;
    heap.push_back({0, 1});
    make_heap(heap.begin(), heap.end(), greater<pair<long long int, long long int>>());
    while (!heap.empty())
    {
        pop_heap(heap.begin(), heap.end(), greater<pair<long long int, long long int>>());
        long long int u = heap.back().second;
        heap.pop_back();
        for (auto &i : graphAdj[u])
        {
            long long int v = i.vertex;
            long long int weight = i.cost;
            if (distance[v] > distance[u] + weight ||
                (distance[v] == distance[u] + weight && fiberUsedToReach[v] != -1 && i.fiberIndices.empty()))
            {
                distance[v] = distance[u] + weight;
                heap.push_back({distance[v], v});
                push_heap(heap.begin(), heap.end(), greater<pair<long long int, long long int>>());
                if (!i.fiberIndices.empty())
                    fiberUsedToReach[v] = i.fiberIndices.back();
                else
                    fiberUsedToReach[v] = fiberUsedToReach[u];
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (fiberUsedToReach[i] != -1)
            fiberUsed[fiberUsedToReach[i]] = true;
    }
    int count = 0;
    for (bool used : fiberUsed)
    {
        if (used)
            count++;
    }
    cout << fibers.size() - count << endl;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<node>> graphAdj(n + 1);
    for (int i = 0; i < m; i++)
    {
        long long int src, dest, c;
        cin >> src >> dest >> c;
        graphAdj[src].push_back(node{dest, c, {}});
        graphAdj[dest].push_back(node{src, c, {}});
    }

    vector<pair<long long int, long long int>> fibers;
    for (int i = 0; i < k; i++)
    {
        long long int src = 1, dest, p;
        cin >> dest >> p;
        graphAdj[src].push_back(node{dest, p, {i}});
        graphAdj[dest].push_back(node{src, p, {i}});
        fibers.push_back({dest, p});
    }

    solve(n, graphAdj, fibers);

    return 0;
}