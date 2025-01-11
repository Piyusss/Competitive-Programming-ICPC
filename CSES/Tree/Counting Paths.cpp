//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class Tree
{
private:
    const ll root = 0;

    const vector<ll> *adjList;
    const ll log2dist;
    vector<ll> par;
    vector<vector<ll>> pow2ends;
    vector<ll> depth;

    void process(ll at, ll prev)
    {
        depth[at] = depth[prev] + 1;
        for (ll n : adjList[at])
        {
            if (n != prev)
            {
                process(n, at);
                par[n] = at;
            }
        }
    }

public:
    Tree(const vector<ll> *adjList, ll size)
        : adjList(adjList), log2dist(ceil(log2(size))), par(size),
          pow2ends(size, vector<ll>(log2dist + 1)), depth(size)
    {
        par[root] = depth[root] = -1;
        process(root, root);

        for (ll n = 0; n < par.size(); n++)
        {
            pow2ends[n][0] = par[n];
        }
        for (ll p = 1; p <= log2dist; p++)
        {
            for (ll n = 0; n < par.size(); n++)
            {
                ll halfway = pow2ends[n][p - 1];
                if (halfway == -1)
                {
                    pow2ends[n][p] = -1;
                }
                else
                {
                    pow2ends[n][p] = pow2ends[halfway][p - 1];
                }
            }
        }
    }

    /** @return the kth parent of node n */
    ll kth_parent(ll n, ll k)
    {
        if (k > par.size())
        {
            return -1;
        }
        ll at = n;
        for (ll pow = 0; pow <= log2dist; pow++)
        {
            if ((k & (1 << pow)) != 0)
            {
                at = pow2ends[at][pow];
                if (at == -1)
                {
                    break;
                }
            }
        }
        return at;
    }

    /** @return the LCA of nodes n1 and n2 */
    ll lca(ll n1, ll n2)
    {
        if (depth[n1] < depth[n2])
        {
            return lca(n2, n1);
        }
        n1 = kth_parent(n1, depth[n1] - depth[n2]);
        if (n1 == n2)
        {
            return n2;
        }

        for (ll i = log2dist; i >= 0; i--)
        {
            if (pow2ends[n1][i] != pow2ends[n2][i])
            {
                n1 = pow2ends[n1][i];
                n2 = pow2ends[n2][i];
            }
        }
        return pow2ends[n1][0];
    }
    /** @return the distance between n1 and n2. */
    ll dist(ll n1, ll n2)
    {
        return depth[n1] + depth[n2] - 2 * depth[lca(n1, n2)];
    }
};

vector<ll> g[200000 + 1];
vector<ll> cnt(200000 + 1);

void dfs(ll node, ll p)
{
    for (auto &c : g[node])
    {
        if (c != p)
        {
            dfs(c, node);
            cnt[node] += cnt[c];
        }
    }
}
void _144()
{
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < n - 1; i++)
    {
        ll a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    Tree tree(g, n);

    while (m--)
    {
        ll x, y;
        cin >> x >> y;
        x--;y--;

        ll lca = tree.lca(x, y);

        cnt[x] += 1;
        cnt[y] += 1;
        cnt[lca] -= 1;

        ll immeadiateParentOfLca = tree.kth_parent(lca, 1);
        if (immeadiateParentOfLca != -1) cnt[immeadiateParentOfLca] -= 1;
    }

    dfs(0, -1);

    for (ll i = 0; i < n; i++)
        cout << cnt[i] << " ";

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
