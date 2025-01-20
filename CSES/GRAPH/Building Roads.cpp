//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
 
//--------------------------------WRITE_HERE-------------------------------------------
 
vector<ll>adjList[100000+1];
 
 
void dfs(ll node,vector<ll> &vis){
    vis[node]=1;
 
    for(auto it:adjList[node]){
        if(!vis[it]){
            dfs(it,vis);
        }
    }
}
 
void _144(){
    ll n,m;
    cin>>n>>m;
 
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
 
        adjList[u].pb(v);
        adjList[v].pb(u);
    }
 
    vector<ll>ans;
    ll cnt=0;
    vector<ll> vis(100000 + 1);
    for(ll i=1;i<=n;i++){
        if(!vis[i]){
            ans.pb(i);
            dfs(i,vis);
            cnt++;
        }
    }
    cout<<cnt-1<<endl;
    ll nu=ans.size();
    for(ll i=0;i<nu-1;i++){
        cout<<ans[i]<<" "<<ans[i+1]<<endl;
    }
 
    return;
 
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
