//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
//--------------------------------WRITE_HERE-------------------------------------------
 
vector<pair<ll,ll>>dir={{0,1},{0,-1},{-1,0},{1,0}};
 
void dfs(ll x, ll y, vector<string> &v, vector<vector<ll>> &vis,ll n,ll m)
{
    vis[x][y]=1;
 
    for(auto it:dir){
        ll nx=x+it.first;
        ll ny=y+it.second;
 
        if (nx >= 0 && nx < n && ny >= 0 
        && ny < m && v[nx][ny] == '.' && !vis[nx][ny])
        {
            dfs(nx,ny,v,vis,n,m);
        }
    }
}
 
void _144(){
    ll n,m;
    cin>>n>>m;
    
    vector<string>v;
    for(ll i=0;i<n;i++){
        string s;
        cin>>s;
        v.pb(s);
    }
 
 
    ll cnt=0;
    vector<vector<ll>>vis(n,vector<ll>(m,0));
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++){
            if(!vis[i][j] && v[i][j]=='.'){
                dfs(i,j,v,vis,n,m);
                cnt++;
            }
        }
    }
 
    cout<<cnt;
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
