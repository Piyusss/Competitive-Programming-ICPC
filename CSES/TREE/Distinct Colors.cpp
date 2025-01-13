#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> g[200001];
vector<ll> val(200001, -1);
set<int> st[200000+1];
vector<ll>res(200000+1);

void dfs(ll node, ll p)
{   st[node].insert(val[node]);

    for(auto &c:g[node]){
        if(c!=p){
            dfs(c,node);
            if(st[node].size()<st[c].size()) swap(st[node],st[c]);
            for(auto &it:st[c]) st[node].insert(it);
        }
    }

    res[node]=st[node].size();
}

void _144()
{
    ll n;
    cin >> n;

    for (ll i = 1; i <= n; i++)
        cin >> val[i];

    for (ll i = 0; i < n - 1; i++)
    {
        ll a, b;
        cin >> a >> b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    for(int i=1;i<=n;i++){
        cout<<res[i]<<" ";
    }

    return;
}

// Main
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t = 1;
    while (t--)
    {
        _144();
    }
}
