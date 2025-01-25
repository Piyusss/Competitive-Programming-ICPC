//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<int> l(200000 + 1), r(200000 + 1);
vector<int> g[200000 + 1];
ll dp[200000 + 1][2];

void dfs(int node, int p)
{
    dp[node][0] = dp[node][1] = 0;

    for (auto &c : g[node])
    {
        if (c != p)
        {
            dfs(c, node);

            dp[node][0] += max(abs(l[node] - l[c]) + dp[c][0],
                               abs(l[node] - r[c]) + dp[c][1]);

            dp[node][1] += max(abs(r[node] - l[c]) + dp[c][0],
                               abs(r[node] - r[c]) + dp[c][1]);
        }
    }
}

void _144()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        g[i].clear();
        int x, y;
        cin >> x >> y;
        l[i] = x;
        r[i] = y;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);

    cout << max(dp[1][0], dp[1][1]) << "\n";
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
