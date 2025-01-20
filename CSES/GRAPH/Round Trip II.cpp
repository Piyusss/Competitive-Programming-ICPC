//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
 
//--------------------------------WRITE_HERE-------------------------------------------
 
 
vector<ll>adjList[100000+1];
vector<ll>temp;
vector<ll>tempCopy;
 
 
bool dfs(ll node,vector<ll>& vis, vector<ll>&pathVis){
    vis[node]=1;
    pathVis[node]=1;
    temp.pb(node);
 
    for(auto it:adjList[node]){
        if(!vis[it]){
            if(dfs(it,vis,pathVis))return 1;
        }
        else if (pathVis[it]){
            temp.pb(it);
            tempCopy=temp;
            return 1;
        }
    }
    temp.pop_back();
    pathVis[node]=0;
    return 0;
}
 
 
void _144(){
    ll n,m;
    cin>>n>>m;
 
    for(ll i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
 
        adjList[u].pb(v);
    }
 
    vector<ll>vis(n+1);
    vector<ll>pathVis(n+1);
    ll flag=0;
    for(ll i=1;i<=n;i++){
        if(!vis[i]){
            temp.clear();
            if(dfs(i,vis,pathVis)){
                flag=1;
                break;
            }
        }
    }
    ll mark=-1; 
    if(flag==1){
        for(ll i=0;i<tempCopy.size();i++){
            if(tempCopy[i]==tempCopy.back()){
                mark=i;
                break;
            }
        }
        cout<<tempCopy.size()-mark<<endl;
        for(ll i=mark;i<tempCopy.size();i++){
            cout<<tempCopy[i]<<" ";
        }
        return;
    }
    cout<<"IMPOSSIBLE";
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
