//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
 
//--------------------------------WRITE_HERE-------------------------------------------
 
 
vector<pair<ll,ll>>adjList[100000+1];
 
 
 
void _144(){
    ll n,m;
    cin>>n>>m;
 
    for(ll i=1;i<=m;i++){
        ll u,v,c;
        cin>>u>>v>>c;
        adjList[u].pb({v,c});
    }
 
    set<pair<ll,ll>>pq;
    pq.insert({0,1});
 
    vector<ll>dis(100000+1,1e18);
    vector<ll>vis(100000+1,0);
    dis[1]=0;
 
    while(!pq.empty()){
        ll d=pq.begin()->first;
        ll node=pq.begin()->second;
 
        pq.erase(pq.begin());
 
        for(auto it:adjList[node]){
            if(d+it.second<dis[it.first]){
                pq.erase({dis[it.first],it.first});
                dis[it.first]=d+it.second;
                pq.insert({dis[it.first],it.first});
            }
        }
    }
 
 
    for(ll i=1;i<=n;i++){
        cout<<dis[i]<<" ";
    }
 
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
