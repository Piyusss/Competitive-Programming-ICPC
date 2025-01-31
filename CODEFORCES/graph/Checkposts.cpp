//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD=1E9+7;
//--------------------------------WRITE_HERE-------------------------------------------

void dfs(ll node, vector<ll> &vis, stack<ll> &st, vector<ll> adjList[])
{
    vis[node] = 1;

    for (auto &it : adjList[node])
    {
        if (!vis[it])
        {
            dfs(it, vis, st, adjList);
        }
    }
    st.push(node);
}

void dfs2(ll node, vector<ll> &vis, vector<ll> adjListRev[], vector<ll> &component)
{
    vis[node] = 1;
    component.push_back(node);

    for (auto &it : adjListRev[node])
    {
        if (!vis[it])
        {
            dfs2(it, vis, adjListRev, component);
        }
    }
}

void _144()
{
    ll n;
    cin >> n;

    vector<ll> coins(n + 1, 0);
    for (ll i = 1; i <= n; i++)
        cin >> coins[i];

    vector<ll> adjList[n + 1];

    ll m;
    cin>>m;
    for (ll i = 0; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
    }

    stack<ll> st;
    vector<ll> vis(n + 1, 0);
    for (ll i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i, vis, st, adjList);
        }
    }

    vector<ll> adjListRev[n + 1];
    for (ll i = 1; i <= n; i++)
    {
        vis[i] = 0;
        for (auto &it : adjList[i])
        {
            adjListRev[it].push_back(i);
        }
    }

    ll id = 0;
    vector<ll> components;
    vector<ll> roots(n + 1, 0);
    ll minCostAdd = 0, minCostWays = 1;

    while (!st.empty())
    {
        auto it = st.top();
        st.pop();
        if (vis[it])
            continue;

        vector<ll> component;
        dfs2(it, vis, adjListRev, component);
        ll mini = INT_MAX;
        ll cnt=0;
        for (auto &u : component)
        {
            roots[u] = id;
            if(coins[u]<mini){
                mini=coins[u];
                cnt=1;
            }
            else if(coins[u]==mini){
                cnt++;
            }
        }
        minCostAdd += mini;
        minCostWays *= cnt;
        minCostWays %= MOD;
    }

    cout<<minCostAdd<<" "<<minCostWays;
    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    // freopen("mootube.in", "r", stdin);
    // freopen("mootube.out", "w", stdout);

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
