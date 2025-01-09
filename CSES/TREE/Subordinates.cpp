//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
vector<ll> g[200001];
vector<ll> cnt(200001,0);

void dfs(ll node,ll p){
    cnt[node] = 1;
    for(auto &c:g[node]){
        if(c!=p){
            dfs(c,node);
            cnt[node] += cnt[c];
        }
    }
}

void _144()
{
    ll n;
    cin>>n;

    for(ll i=2;i<=n;i++){
        ll x;
        cin>>x;

        g[i].push_back(x);
        g[x].push_back(i);
    }

    dfs(1,-1);

    for(ll i=1;i<=n;i++){
        cout << cnt[i]-1 << " ";
    }

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
