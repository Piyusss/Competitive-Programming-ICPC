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
    ll n,q;
    cin>>n>>q;

    DisjointSet ds(n);
    vector<pair<ll,pair<ll,ll>>>edges;
    for(int i=0;i<n-1;i++){
        ll p,q,r;
        cin>>p>>q>>r;
        edges.push_back({r,{p,q}});
    }

    vector<pair<ll,pair<ll,ll>>>queries;
    for (int i = 0; i < q; i++){
        ll k,v;
        cin>>k>>v;
        queries.push_back({k,{v,i}});
    }

    sort(edges.begin(),edges.end(),greater<pair<ll,pair<ll,ll>>>());
    sort(queries.begin(),queries.end(),greater<pair<ll,pair<ll,ll>>>());
    
    ll idx=0;
    vector<ll>res(q);
    for(auto &it:queries){
        ll reqK=it.first;
        while(idx<edges.size() && edges[idx].first>=reqK){
            ds.unionBySize(edges[idx].second.first,edges[idx].second.second);
            idx++;
        }
        res[it.second.second]=ds.sizeOfComponent(ds.findUPar(it.second.first))-1;
    }

    for(auto &it:res) cout<<it<<endl;
    return;

}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

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
