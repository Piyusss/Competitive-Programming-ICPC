//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
//--------------------------------WRITE_HERE-------------------------------------------
 
vector<ll> adjList[100000 + 1];
vector<ll> col(100000 + 1, -1);
 
bool dfs(ll node, ll c)
{
    col[node] = c;
 
    for (auto it : adjList[node])
    {
        if (col[it] == -1)
        {
            if (!dfs(it, c ^ 1))
                return 0;
        }
        else
        {
            if (col[it] == col[node])
                return 0;
        }
    }
    return 1;
}
 
void _144()
{
    ll n, k;
    cin >> n >> k;
 
 
    for (ll i = 1; i <= k; i++)
    {
        ll u, v;
        cin >> u >> v;
        adjList[u].pb(v);
        adjList[v].pb(u);
    }
 
    // now
    for (ll i = 1; i <= n; i++)
    {
        if (col[i] == -1)
        {
            if (!dfs(i, 0))
            {
                cout<<"IMPOSSIBLE";
                return;
            }
        }
    }
 
    for(ll i=1;i<=n;i++){
        if(col[i]==0)col[i]=1;
        else col[i]=2;
    }
    for(ll i=1;i<=n;i++){
        cout<<col[i]<<" ";
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
        // TC++;
    }
}
