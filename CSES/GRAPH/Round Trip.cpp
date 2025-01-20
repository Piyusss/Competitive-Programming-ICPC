//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
 
//--------------------------------WRITE_HERE-------------------------------------------
 
 
vector<ll>adjList[100000+1];
vector<ll>temp;
vector<ll>wait;
 
bool dfs(ll node, vector<ll> &vis, ll par)
{
    vis[node]=1;
    temp.pb(node);
 
    for(auto it:adjList[node]){
        if(!vis[it]){
            if(dfs(it,vis,node))return 1;
        }
        else if(it!=par){
            temp.pb(it);
            wait=temp;
            return 1;
        }
    }
    temp.pop_back();
    return 0;
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
 
    ll flag=0;
    vector<ll>vis(100000+1);
    for(ll i=1;i<=n;i++){
        if(!vis[i]){
            temp.clear();wait.clear();
            if(dfs(i,vis,-1)){
                flag=1;
                break;
            }
        }
    }
 
    if(flag==0){
        cout<<"IMPOSSIBLE";
        return;
    }
 
    //now
    vector<ll>ans;
    ll mark=0;
    for(ll i=0;i<wait.size();i++){
        if(wait[i]==wait.back()){
            mark=i;
            break;
        }
    }
 
    for(ll j=mark;j<wait.size();j++)ans.pb(wait[j]);
 
    cout<<ans.size()<<endl;
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
