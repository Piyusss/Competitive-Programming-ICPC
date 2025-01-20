//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
 
//--------------------------------WRITE_HERE-------------------------------------------
 
 
vector<ll>adjList[2500+1];
vector<pair<pair<ll,ll>,ll>>edges;
ll mark=0;
 
void dfs(ll node, vector<ll> &vis)
{
    vis[node]=1;
    for(auto it:adjList[node]){
        if(!vis[it])dfs(it,vis);
    }
}
void dfs2(ll node, vector<ll> &vis2)
{
    vis2[node]=1;
    for(auto it:adjList[node]){
        if(!vis2[it])dfs2(it,vis2);
    }
}
 
void _144(){
    ll n,m;
    cin>>n>>m;
 
    for(ll i=1;i<=m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
 
        edges.pb({{u,v},w});
        adjList[u].pb(v);
    }
 
    vector<ll>dis(2500+1,-1e18);
    vector<ll>vis(2500+1);
    vector<ll>vis2(2500+1);
    dis[1]=0;
 
    for(ll iter=1;iter<=n;iter++){
        for(auto it:edges){
            ll u=it.first.first;
            ll v=it.first.second;
            ll w=it.second;
 
            if(dis[u]+w>dis[v]){
                if(iter==n){
                    dfs(v,vis);dfs2(1,vis2);
                    if(vis[n]==1 && vis2[v]){
                        cout<<"-1";return;
                    }
                }
                if(iter!=n)dis[v]=dis[u]+w;
            }
        }
    }
 
    cout<<dis[n];
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
