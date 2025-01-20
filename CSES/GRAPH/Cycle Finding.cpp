//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
 
//--------------------------------WRITE_HERE-------------------------------------------
 
vector<pair<ll, ll>> adjList[2500 + 1];
vector<pair<pair<ll, ll>, ll>> edges;
 
void _144()
{
    ll n, m;
    cin >> n >> m;
 
    for (ll i = 1; i <= m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        adjList[u].pb({v, w});
        edges.pb({{u, v}, w});
    }
 
    vector<ll> dis(2500 + 1);
    vector<ll> par(2500 + 1, -1);
 
    vector<ll> ans;
    ll mark;
    for (ll iter = 1; iter <= n; iter++)
    {   mark=-1;
        for (auto it : edges)
        {
            ll u = it.first.first;
            ll v = it.first.second;
            ll w = it.second;
 
            if (dis[u] + w < dis[v])
            { 
                dis[v] = dis[u] + w;
                par[v] = u;
                mark=v;
            }
        }
    }
 
 
    //now
    if(mark==-1){
        cout<<"NO";return;
    }
 
    cout<<"YES"<<endl;
 
    ll y=mark;
    for(ll i=1;i<=n;i++)y=par[y];
        for (int cur = y;; cur = par[cur]) {
            ans.push_back(cur);
            if (cur == y && ans.size() > 1)
                break;
        }
        reverse(ans.begin(), ans.end());
    for(auto it:ans)cout<<it<<" ";
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
