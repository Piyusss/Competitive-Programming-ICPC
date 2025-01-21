#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

int n, m, q;
const int MAXN = 2E5 + 1;
const int LOGN = 18;
vector<pair<int, int>> g[MAXN];

class DisjointSet
{
    vector<int> rank, parent, sizee;

public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        sizee.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
            sizee[i] = 1;
        }
    }

    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;
        if (rank[ulp_u] < rank[ulp_v])
        {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u])
        {
            parent[ulp_v] = ulp_u;
        }
        else
        {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;
        if (sizee[ulp_u] < sizee[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            sizee[ulp_v] += sizee[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            sizee[ulp_u] += sizee[ulp_v];
        }
    }

    int sizeOfComponent(int ult_p)
    {
        return sizee[ult_p];
    }
};

class LCA
{
    vector<int> dep;
    vector<vector<int>> par, val;
    vector<pair<int, int>> *graph;
    int nodeCount;

public:
    LCA(vector<pair<int, int>> *g, int n)
        : graph(g), nodeCount(n), dep(n + 1, -1),
          par(n + 1, vector<int>(LOGN, 0)),
          val(n + 1, vector<int>(LOGN, 0)) {}

    void dfs_init(int u, int p, int d)
    {
        dep[u] = d;
        par[u][0] = p;
        for (auto &it : graph[u])
        {
            int v = it.first;
            int w = it.second;
            if (v != p)
            {
                val[v][0] = w;
                dfs_init(v, u, d + 1);
            }
        }
    }

    void init()
    {
        for (int i = 1; i <= nodeCount; i++)
        {
            if (dep[i] == -1)
            {
                dfs_init(i, i, 0);
            }
        }

        for (int k = 1; k < LOGN; k++)
        {
            for (int i = 1; i <= nodeCount; i++)
            {
                par[i][k] = par[par[i][k - 1]][k - 1];
                val[i][k] = max(val[i][k - 1], val[par[i][k - 1]][k - 1]);
            }
        }
    }

    int query(int a, int b)
    {
        if (dep[a] > dep[b])
        {
            swap(a, b);
        }

        int ans = 0;
        for (int d = LOGN - 1; d >= 0; d--)
        {
            if (dep[b] - (1 << d) >= dep[a])
            {
                ans = max(ans, val[b][d]);
                b = par[b][d];
            }
        }

        if (a == b)
        {
            return ans;
        }

        for (int d = LOGN - 1; d >= 0; d--)
        {
            if (par[a][d] != par[b][d])
            {
                ans = max(ans, val[a][d]);
                ans = max(ans, val[b][d]);
                a = par[a][d];
                b = par[b][d];
            }
        }

        if (par[a][0] != par[b][0])
            return -1;

        ans = max(ans, val[a][0]);
        ans = max(ans, val[b][0]);

        return ans;
    }
};

void _144()
{
    cin >> n >> m >> q;

    DisjointSet ds(n);

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        if (ds.findUPar(u) != ds.findUPar(v))
        {
            ds.unionBySize(u, v);
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
        }
    }

    LCA lca(g, n);
    lca.init();

    while (q--)
    {
        int x, y;
        cin >> x >> y;

        int minNoOfDays = lca.query(x, y);
        cout << minNoOfDays << "\n";
    }
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
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
