//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
const int MAXN = 2E5 + 1;

void bridgeDfs(int node, int p, vector<pair<ll, ll>> &store,
               vector<ll> &level, vector<ll> &dp, vector<ll> g[], vector<ll> g2[],
               vector<pair<ll, ll>> &bridges)
{

    for (auto &c : g[node])
    {
        if (level[c] == 0)
        {
            store.push_back({node, c});
            g2[node].push_back(c);
            level[c] = level[node] + 1;
            bridgeDfs(c, node, store, level, dp, g, g2, bridges);
            dp[node] += dp[c];
        }
        else
        {
            if (c != p)
            {
                if (level[c] < level[node])
                {
                    dp[node]++;
                }
                else if (level[c] > level[node])
                {
                    dp[node]--;
                    store.push_back({c, node});
                }
            }
        }
    }

    if (level[node] >= 2 && dp[node] == 0)
    {
        bridges.push_back({node, p});
    }
}

void dfsForSubtreeNos(ll node, ll p, vector<ll> g[], vector<ll> &sub)
{
    sub[node] = 1;

    for (auto &c : g[node])
    {
        if (c != p)
        {
            dfsForSubtreeNos(c, node, g, sub);
            sub[node] += sub[c];
        }
    }
}

void _144()
{
    ll n, m;
    cin >> n >> m;

    vector<ll> g[n + 1], g2[n + 1];
    vector<ll> level(n + 1);
    vector<pair<ll, ll>> store;
    vector<ll> dp(n + 1);

    for (int i = 0; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    level[1] = 1;
    vector<pair<ll, ll>> bridge;
    bridgeDfs(1, -1, store, level, dp, g, g2, bridge);

    // cout<<"Levels:"<<"\n";
    // for(int i=1;i<=n;i++) cout<<level[i]<<" ";
    // cout<<endl;

    // cout<<"Bridges:"<<"\n";
    // for(int i=0;i<bridge.size();i++) cout<<bridge[i].first<<" "<<bridge[i].second<<"\n";
    // cout<<endl;

    vector<ll> cnts(n + 1);
    dfsForSubtreeNos(1, -1, g2, cnts);

    ll tot = (n * (n - 1)) / 2;
    ll maxi = 0;
    for (auto &b : bridge)
    {
        int u = b.first;
        int v = b.second;

        // cout<<"Counts:"<<"\n";
        // cout << cntU << " " << cntV << endl;
        bool levelUp = cnts[u] < cnts[v];

        if (levelUp)
        {
            maxi = max(maxi, ((cnts[u]) * (n - cnts[u])));
        }
        else
        {
            maxi = max(maxi, ((cnts[v]) * (n - cnts[v])));
        }
    }

    cout << tot - maxi << "\n";
    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    // freopen("input.in", "r",stdin);
    // freopen("output.out", "w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t = 1;
    cin >> t;
    while (t--)
    {
        _144();
    }
}
