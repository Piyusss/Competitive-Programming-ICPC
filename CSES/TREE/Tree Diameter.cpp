//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<ll>g[200000+1];
vector<ll>dis(200000+1);

void dfs(ll node,ll p){
    for(auto &c:g[node]){
        if(c!=p){
            dis[c]=dis[node]+1;
            dfs(c,node);
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

    ll firstFarNode=-1;
    ll maxi=0;
    for(ll i=1;i<=n;i++){
        if(dis[i] > maxi){
            maxi=dis[i];
            firstFarNode=i;
        }
    }

    for(ll i=1;i<=n;i++) dis[i]=0;

    ll res = 0;
    dfs(firstFarNode,-1);
    for(ll i=1;i<=n;i++) res=max(res,dis[i]);

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
