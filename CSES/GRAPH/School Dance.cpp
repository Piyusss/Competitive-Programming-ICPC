//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
struct HopcroftKarp
{
    const int INF = 1e9;
    int n, m;
    vector<int> match, dist;
    vector<vector<int>> g;

    HopcroftKarp(int n, int m) : n(n), m(m), match(n + m + 1, 0), dist(n + m + 1, 0), g(n + m + 1) {}

    void addEdge(int u, int v)
    {
        v += n;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool bfs()
    {
        queue<int> q;
        for (int node = 1; node <= n; node++)
        {
            if (!match[node])
            {
                q.push(node);
                dist[node] = 0;
            }
            else
            {
                dist[node] = INF;
            }
        }

        dist[0] = INF;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            if (dist[node] >= dist[0])
                continue;

            for (int neighbor : g[node])
            {
                if (dist[match[neighbor]] == INF)
                {
                    dist[match[neighbor]] = dist[node] + 1;
                    q.push(match[neighbor]);
                }
            }
        }

        return dist[0] != INF;
    }

    bool dfs(int node)
    {
        if (node == 0)
            return true;

        for (int neighbor : g[node])
        {
            if (dist[match[neighbor]] == dist[node] + 1 && dfs(match[neighbor]))
            {
                match[node] = neighbor;
                match[neighbor] = node;
                return true;
            }
        }

        dist[node] = INF;
        return false;
    }

    int maxMatching()
    {
        int matching = 0;

        while (bfs())
        {
            for (int node = 1; node <= n; node++)
            {
                if (!match[node] && dfs(node))
                {
                    matching++;
                }
            }
        }

        return matching;
    }

    void printMatching()
    {
        cout << maxMatching() << '\n';

        for (int node = 1; node <= n; node++)
        {
            if (match[node])
            {
                cout << node << ' ' << match[node] - n << '\n';
            }
        }
    }
};

void _144()
{
    ll n,m,k;
    cin>>n>>m>>k;

    HopcroftKarp hk(n,m);

    for(ll i=0;i<k;i+=1){
        ll u, v;
        cin>>u>>v;
        hk.addEdge(u,v);
    }

    hk.printMatching();
    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t = 1;
    // cin >> t;
    while (t--)
    {
        _144();
    }
}
