//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
//--------------------------------WRITE_HERE-------------------------------------------
 
class DisjointSet {
    vector<int> rank, parent, sizee;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        sizee.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            sizee[i] = 1;
        }
    }
 
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }
 
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
 
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (sizee[ulp_u] < sizee[ulp_v]) {
            parent[ulp_u] = ulp_v;
            sizee[ulp_v] += sizee[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            sizee[ulp_u] += sizee[ulp_v];
        }
    }
 
    int sizeOfComponent(int ult_p){
        return sizee[ult_p];
    }
 
};
 
int cnt=0;
 
void dfs(int node,vector<int>&vis,vector<int>new_adjList[]){
    cnt+=1;
    vis[node]=1;
 
    for(auto &it:new_adjList[node]){
        if(!vis[it]){
            dfs(it,vis,new_adjList);
        }
    }
}
 
void _144()
{
    ll n,m;
    cin>>n>>m;
 
    vector<pair<ll, pair<ll, ll>>> edges;
    for(ll i=0;i<m;i+=1){
        ll u,v,c;
        cin>>u>>v>>c;
        edges.push_back({c,{u,v}});
    }
 
    sort(edges.begin(),edges.end());
 
    DisjointSet ds(n);
 
    ll res=0;
    vector<int>new_adjList[n+1];
    for(auto &it:edges){
        ll c=it.first;
        ll u=it.second.first;
        ll v=it.second.second;
 
        if(ds.findUPar(u) != ds.findUPar(v)){
            res += c;
            new_adjList[u].push_back(v);
            new_adjList[v].push_back(u);
            ds.unionBySize(u,v);
        }
    }
 
    vector<int>vis(n+1);
    dfs(1,vis,new_adjList);
 
    if(cnt!=n){
        cout<<"IMPOSSIBLE";
        return;
    }
 
    cout<<res;
    return;
 
 
}
 
//--------------------------------END--------------------------------------------------
 
// Main
int main()
{
	//freopen("input.in", "r", stdin);
	//freopen("output.out", "w", stdout);
 
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
