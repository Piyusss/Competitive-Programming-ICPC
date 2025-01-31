//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

ll dpThis(ll endNode, ll node, vector<ll> &dp, vector<vector<ll>> &adjCond, vector<ll> &comp_sum, vector<ll> &roots)
{

    if (dp[node] != -1)
        return dp[node];

    ll res = 0;

    for (auto &it : adjCond[node])
    {   if(node==endNode) continue;
        res = max(res, dpThis(endNode, it, dp, adjCond, comp_sum, roots));
    }

    return dp[node] = comp_sum[node] + res;
}

void _144()
{
    ll n, m, s, e;
    cin >> n >> m >> s >> e;

    vector<ll> coins(n + 1, 0);
    for (ll i = 1; i <= n; i++)
        cin >> coins[i];

    vector<ll> adjList[n + 1];
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

    ll noOfScc = 0;
    ll id = 0;
    vector<ll> components;
    vector<ll> roots(n + 1, 0), comp_sum;
    while (!st.empty())
    {
        auto it = st.top();
        st.pop();
        if (vis[it])
            continue;

        vector<ll> component;
        dfs2(it, vis, adjListRev, component);
        noOfScc += 1;
        ll sum = 0;
        for (auto &u : component)
        {
            roots[u] = id;
            sum += coins[u];
        }
        comp_sum.push_back(sum);
        id += 1;
    }

    // Make Condensation Graph
    vector<vector<ll>> adjCond;
    adjCond.assign(n + 1, {});
    for (ll v = 1; v <= n; v++)
    {
        for (auto &u : adjList[v])
        {
            if (roots[v] != roots[u])
            {
                adjCond[roots[v]].push_back(roots[u]);
            }
        }
    }

    vector<ll> dp(noOfScc + 1, -1);
    ll res = 0;
    res = max(res, dpThis(roots[e], roots[s], dp, adjCond, comp_sum, roots));

    cout << res;
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
