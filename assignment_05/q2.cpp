#include <bits/stdc++.h>
using namespace std;

const long long int INF = LLONG_MAX;

typedef struct node
{
    long long int vertex;
    long long int cost;
    int fiberIndex;
} node;

void solve(int n, vector<vector<node>> &graphAdj, vector<pair<long long int, long long int>> &fibers)
{
    vector<long long int> distance(n + 1, INF);
    vector<int> fiberUsedToReach(n + 1, -1);
    unordered_set<int> fiberUsed;

    distance[1] = 0;
    priority_queue<pair<long long int, long long int>, vector<pair<long long int, long long int>>, greater<pair<long long int, long long int>>> pq;
    pq.push({0, 1});

    while (!pq.empty())
    {
        long long int u = pq.top().second;
        pq.pop();
        for (auto &i : graphAdj[u])
        {
            long long int v = i.vertex;
            long long int weight = i.cost;
            if (distance[v] > distance[u] + weight || (distance[v] == distance[u] + weight && fiberUsedToReach[v] != -1 && i.fiberIndex == -1))
            {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
                if (i.fiberIndex != -1)
                    fiberUsedToReach[v] = i.fiberIndex;
                else
                    fiberUsedToReach[v] = fiberUsedToReach[u];
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (fiberUsedToReach[i] != -1)
            fiberUsed.insert(fiberUsedToReach[i]);
    }
    
    cout << fibers.size() - fiberUsed.size() << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<node>> graphAdj(n + 1);
    graphAdj.reserve(n+1);
    for (int i = 0; i < m; i++)
    {
        long long int src, dest, c;
        cin >> src >> dest >> c;
        graphAdj[src].push_back(node{dest, c, -1});
        graphAdj[dest].push_back(node{src, c, -1});
    }
    
    vector<pair<long long int, long long int>> fibers;
    fibers.reserve(k);
    for (int i = 0; i < k; i++)
    {
        long long int src = 1, dest, p;
        cin >> dest >> p;
        graphAdj[src].push_back(node{dest, p, i});
        graphAdj[dest].push_back(node{src, p, i});
        fibers.push_back({dest, p});
    }

    solve(n, graphAdj, fibers);

    return 0;
}