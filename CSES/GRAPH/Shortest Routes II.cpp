//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
 
//--------------------------------WRITE_HERE-------------------------------------------
 
void _144(){
    ll n,m,q;
    cin>>n>>m>>q;
 
    vector<vector<ll>>dis(n+1,vector<ll>(n+1,1e18));
    for(ll i=1;i<=n;i++)dis[i][i]=0;
 
    for(ll i=1;i<=m;i++){
        ll u,v,c;
        cin>>u>>v>>c;
        dis[u][v]=dis[v][u]=min(dis[v][u],c);
    }
 
 
 
    for(ll k=1;k<=n;k++){
        for(ll i=1;i<=n;i++){
            for(ll j=1;j<=n;j++){
                if(dis[i][k]!=1e18 && dis[k][j]!=1e18){
                    dis[i][j]=dis[j][i]=min(dis[j][i],dis[i][k]+dis[k][j]);
                }
            }
        }
    }
 
 
    for(ll i=1;i<=q;i++){
        ll a,b;
        cin>>a>>b;
 
        if(dis[a][b]==1e18)cout<<"-1"<<endl;
        else cout<<dis[a][b]<<endl;
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
