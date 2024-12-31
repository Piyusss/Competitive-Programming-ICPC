//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
//--------------------------------WRITE_HERE-------------------------------------------
 
vector<ll>res;
 
void eulerianDfs(ll node,vector<vector<ll>>&g){
    while(!g[node].empty()){
        ll child=g[node].back();
        g[node].pop_back();
        eulerianDfs(child,g);
    }
    res.push_back(node);
}
 
void _144()
{
    ll n,m;
    cin>>n>>m;
 
    vector<vector<ll>>g(n);
    vector<ll>indeg(n),outdeg(n);
    
    for(ll i=0;i<m;i+=1){
        ll a,b;
        cin>>a>>b;
 
        a-=1;b-=1;
        g[a].push_back(b);
 
        outdeg[a]+=1;
        indeg[b]+=1;
    }
 
    bool flag=1;
    for(ll i=1;i<=n-2;i+=1){
        if(indeg[i]!=outdeg[i]){
            cout<<"IMPOSSIBLE";
            return;
        }
    }
 
    if(outdeg[0]-indeg[0]!=1 || indeg[n-1]-outdeg[n-1]!=1) {
        cout<<"IMPOSSIBLE";
        return;
    }
 
    eulerianDfs(0,g);
    reverse(res.begin(), res.end());
  
    //Check if all edges are getting used or not
    if(m+1 != res.size()){
        cout<<"IMPOSSIBLE";
        return;
    }
    
    for(auto &it:res){
        cout<<it+1<<" ";
    }
 
    return;
}
 
//--------------------------------END--------------------------------------------------
 
// Main
int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.out", "w", stdout);
 
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
