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

void _144()
{
    int n;cin>>n;

    DisjointSet ds(n);
    vector<pair<int,int>>red;

    for(int i=0;i<n-1;i++){
        int x,y;cin>>x>>y;

        if(ds.findUPar(x)!=ds.findUPar(y)){
            ds.unionBySize(x,y);
        }
        else{
            red.push_back({x,y});
        }
    }

    vector<int>pars;
    for(int i=1;i<=n;i++){
        if(ds.findUPar(i)==i){
            pars.push_back(i);
        }
    }

    cout<<pars.size()-1<<"\n";

    for(int i=0;i<pars.size()-1;i++){
        int f=pars[i];
        int s=pars[i+1];
        pair<int,int>p=red.back();
        cout<<p.first<<" "<<p.second<<" "<<f<<" "<<s<<"\n";
        red.pop_back();
    }

    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
//freopen("input.in", "r",stdin);
//freopen("output.out", "w",stdout);

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
