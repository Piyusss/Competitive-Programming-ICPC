//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class DisjointSet
{
    vector<int> rank, parent, sizee;
    int noOfComponents;

public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        sizee.resize(n + 1);
        noOfComponents = n;

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
        noOfComponents--;
    }

    int sizeOfComponent(int ult_p)
    {
        return sizee[ult_p];
    }
    int findNoOfComponents()
    {
        return noOfComponents;
    }
};

void _144()
{
    ll n, m;
    cin >> n >> m;

    DisjointSet ds(n);
    vector<int> adjList[n + 1];

    for (int i = 1; i <= m; i++)
    {
        ll u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<int> existence(n + 1);
    vector<string> res;
    vector<ll>queries;
    int tot = 0;
    for (int i = 1; i <= n; i++)
    {
        ll x;
        cin >> x;
        queries.push_back(x);
    }

    for(ll i=queries.size()-1;i>=0;i--){
        ll x=queries[i];
        
        existence[x] = 1;
        tot++;
        for (auto it : adjList[x])
        {
            if (existence[it] == 1 && ds.findUPar(it) != ds.findUPar(x))
            {
                ds.unionBySize(it, x);
                tot--;
            }
        }
        if (tot == 1)
        {
            res.push_back("YES");
        }
        else
            res.push_back("NO");
    }

    reverse(res.begin(), res.end());

    for (auto &it : res)
        cout << it << endl;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

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
