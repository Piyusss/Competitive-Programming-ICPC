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
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        ds.unionBySize(u, v);
    }

    int noOfTots = ds.noOfComponents();
    cout << noOfTots << " ";

    ll pr = 1;
    for (int i = 1; i <= n; i++)
    {
        if (ds.findUPar(i) == i)
        {
            pr = (pr * ds.sizeOfComponent(i)) % MOD;
        }
    }

    cout << pr % MOD << "\n";

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
