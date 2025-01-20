//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
 
//--------------------------------WRITE_HERE-------------------------------------------
 
vector<ll>adjList[100000+1];
 
 
void _144(){
    ll n,m;
    cin>>n>>m;
 
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        adjList[u].pb(v);
        adjList[v].pb(u);
    }
 
    priority_queue<pair<ll,ll> ,
    vector<pair<ll,ll>> , greater<pair<ll,ll>>>pq;
 
    pq.push({0,1});
 
    vector<ll>dis(n+1,1e9);
    dis[1]=0;
    vector<ll>store(n+1);
 
    while(!pq.empty()){
        ll d=pq.top().first;
        ll node=pq.top().second;
 
        pq.pop();
 
        for(auto it:adjList[node]){
            if(dis[node]+1<dis[it]){
                dis[it]=dis[node]+1;
                pq.push({dis[it],it});
                store[it]=node;
            }
        }
    }
 
    if(dis[n]==1e9){
        cout<<"IMPOSSIBLE";
        return;
    }
    cout<<dis[n]+1<<endl;
 
    vector<ll>ans;
    ans.pb(n);
    ll flag=n;
    for(ll i=1;i<=dis[n];i++){
        ans.pb(store[flag]);
        flag=store[flag];
    }
    reverse(ans.begin(),ans.end());
 
    for(auto it:ans){
        cout<<it<<" ";
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
