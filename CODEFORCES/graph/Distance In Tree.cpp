//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5E4 + 1;
//--------------------------------WRITE_HERE-------------------------------------------

vector<int> g[MAXN];
ll res = 0;
int n, k;
int dp[MAXN][501];

void dfs(int node, int p)
{
    dp[node][0] = 1;

    for (auto &c : g[node])
    {
        if (c != p)
        {
            dfs(c, node);

            for (int i = 1; i <= k; i++)
            {
                dp[node][i] += dp[c][i - 1];
            }
        }
    }
    res += dp[node][k];

    ll full = 0;
    for (auto &c : g[node])
    {
        if (c != p)
        {
            for (int i = 1; i <= k - 1; i++)
            {
                full += (dp[c][i - 1]) * (dp[node][k - i] - dp[c][k - i - 1]);
            }
        }
    }
    res += (full>>1);
}

void _144()
{
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);

    cout << res;
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
    // cin >> t;
    while (t--)
    {
        _144();
    }
}
