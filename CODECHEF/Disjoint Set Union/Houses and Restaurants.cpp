//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

const int MOD = 1E9 + 7;
class DisjointSet
{
    vector<int> rank, parent, sizee;
    int tot;

public:
    DisjointSet(int n)
    {
        tot = n;
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
        tot--;
    }

    void unionBySize(int u, int v, vector<int> &vis)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;
        if (sizee[ulp_u] < sizee[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            sizee[ulp_v] += sizee[ulp_u];
            vis[ulp_v] |= vis[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            sizee[ulp_u] += sizee[ulp_v];
            vis[ulp_u] |= vis[ulp_v];
        }

        tot--;
    }

    int sizeOfComponent(int ult_p)
    {
        return sizee[ult_p];
    }
    int noOfComponents()
    {
        return tot;
    }
};

void _144()
{

    int n, m;
    cin >> n >> m;

    DisjointSet ds(n);

    string s;
    cin >> s;
    vector<int> vis(n + 1);

    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'R')
            vis[i + 1] = 1;
    }

    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        edges.push_back({z, {x, y}});
    }

    sort(edges.begin(), edges.end());

    ll res = 0;
    for (auto &it : edges)
    {
        int w = it.first;
        int u = it.second.first;
        int v = it.second.second;

        if (w <= 0)
        {
            ds.unionBySize(u, v, vis);
            res += w;
        }
        else
        {
            int ultU = ds.findUPar(u);
            int ultV = ds.findUPar(v);

            if (ultU != ultV)
            {
                if (vis[ultU] == 0 || vis[ultV] == 0)
                {
                    ds.unionBySize(u, v, vis);
                    res += w;
                }
            }
        }
    }

    cout << res << "\n";
    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    // freopen("input.in", "r",stdin);
    // freopen("output.out", "w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t = 1;
    cin >> t;
    while (t--)
    {
        _144();
    }
}
