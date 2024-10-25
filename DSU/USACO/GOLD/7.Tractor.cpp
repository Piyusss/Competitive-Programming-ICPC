//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
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

ll fix;
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

bool check(ll mid, vector<vector<ll>> &field, ll n)
{
    DisjointSet ds(n * n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ll x = i;
            ll y = j;
            ll val = field[x][y];

            for (auto &it : dir)
            {
                ll nx = x + it[0];
                ll ny = y + it[1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < n && abs(field[x][y] - field[nx][ny]) <= mid)
                {
                    ds.unionBySize(i*n+j,nx*n+ny);
                }
            }
        }
    }

    for(int i=0;i<n*n;i++){
        if(ds.sizeOfComponent(i) >= fix) return 1;
    }

    return 0;
}

void _144()
{
    ll n;
    cin >> n;

    fix = ((n*n) + 2 - 1) / 2;
    vector<vector<ll>> field(n,vector<ll>(n,0));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
        {
            cin>>field[i][j];
        }
    }

    ll low = 0;
    ll high = 1e9;
    ll res = -1;

    while (low <= high)
    {
        ll mid = low + (high - low) / 2;

        if (check(mid, field, n))
        {
            res = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }

    cout << res << endl;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);

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
