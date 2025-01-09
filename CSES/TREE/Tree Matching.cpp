//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<ll>g[200000+1];
vector<ll>vis(200000+1);
ll res=0;

void dfs(ll node,ll p){
    for(auto &c:g[node]){
        if(c!=p){
            dfs(c,node);
            if(!vis[node] && !vis[c]){
                vis[node]=vis[c]=1;
                res++;
            }
        }
    }
}

void _144()
{
    ll n;
    cin>>n;

    for(ll i=1;i<=n-1;i++){
        ll a,b;
        cin>>a>>b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1,-1);

    cout<<res;

    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
//freopen("input.in", "r",stdin);
//freopen("output.out", "w",stdout);

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
