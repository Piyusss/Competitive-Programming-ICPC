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
static bool comp(pair<ll,pair<ll,ll>>&a,pair<ll,pair<ll,ll>>&b){
    return a.first < b.first;
}

bool f(ll mid,vector<ll> &cow_positions,ll n,vector<pair<ll,pair<ll,ll>>>&wormholes){
    DisjointSet ds(n);

    for(auto &it:wormholes){
        ll k=it.first;
        ll u=it.second.first;
        ll v=it.second.second;
        if(k>=mid) ds.unionBySize(u,v);
    }

    for(int i=0;i<n;i++){
        if(ds.findUPar(i+1) != ds.findUPar(cow_positions[i])) return 0;
    }
    return 1;
}

void _144()
{   
    ll n,m;
    cin>>n>>m;

    vector<ll>cow_positions(n);
    bool flag=0;
    for(int i=0;i<n;i++){
        cin >> cow_positions[i];
        if(cow_positions[i]!=i+1)flag=1;
    }
    if(flag==0){
        cout<<"-1"<<endl;
        return;
    }

    ll maxi=0;
    vector<pair<ll,pair<ll,ll>>>wormholes;
    for(int i=1;i<=m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        maxi=max(maxi,w);
        wormholes.push_back({w,{u,v}});
    }

    sort(wormholes.begin(),wormholes.end(),comp);

    ll low=1;
    ll high=maxi;
    ll res=-1;
    while(low<=high){
        ll mid = (low) + (high - low) / 2;

        if (f(mid, cow_positions, n, wormholes))
        {
            res=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }

    cout<<res<<endl;
    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);

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
