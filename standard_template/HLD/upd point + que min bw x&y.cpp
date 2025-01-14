//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class HLD
{
private:
    const ll N;
    const ll D;
    const ll S;

    vector<ll> v, st, sz, p, dep, id, tp;
    vector<vector<ll>> adj;
    ll ct;

    void update(ll idx, ll val)
    {
        st[idx += N] = val;
        for (idx /= 2; idx; idx /= 2)
            st[idx] = min(st[2 * idx], st[2 * idx + 1]);
    }

    ll query(ll lo, ll hi)
    {
        ll ra = LLONG_MAX, rb = LLONG_MAX;
        for (lo += N, hi += N + 1; lo < hi; lo /= 2, hi /= 2)
        {
            if (lo & 1)
                ra = min(ra, st[lo++]);
            if (hi & 1)
                rb = min(rb, st[--hi]);
        }
        return min(ra, rb);
    }

    ll dfs_sz(ll cur, ll par)
    {
        sz[cur] = 1;
        p[cur] = par;
        for (ll chi : adj[cur])
        {
            if (chi == par)
                continue;
            dep[chi] = dep[cur] + 1;
            sz[cur] += dfs_sz(chi, cur);
        }
        return sz[cur];
    }

    void dfs_hld(ll cur, ll par, ll top)
    {
        id[cur] = ct++;
        tp[cur] = top;
        update(id[cur], v[cur]);
        ll h_chi = -1, h_sz = -1;
        for (ll chi : adj[cur])
        {
            if (chi == par)
                continue;
            if (sz[chi] > h_sz)
            {
                h_sz = sz[chi];
                h_chi = chi;
            }
        }
        if (h_chi == -1)
            return;
        dfs_hld(h_chi, cur, top);
        for (ll chi : adj[cur])
        {
            if (chi == par || chi == h_chi)
                continue;
            dfs_hld(chi, cur, chi);
        }
    }

public:
    HLD(ll n) : N(n + 1), D(19), S(1 << D), ct(1), v(N), st(S), sz(N), p(N), dep(N), id(N), tp(N), adj(N) {}

    void add_edges(vector<ll> edges[])
    {
        for (ll i = 1; i < N; i++)
        {
            for (ll neighbor : edges[i])
            {
                adj[i].push_back(neighbor);
            }
        }
    }

    void set_value(ll idx, ll value)
    {
        v[idx] = value;
    }

    void initialize()
    {
        dfs_sz(1, 1);
        dfs_hld(1, 1, 1);
    }

    void update_node(ll idx, ll value)
    {
        v[idx] = value;
        update(id[idx], value);
    }

    ll query_path_min(ll x, ll y)
    {
        ll ret = LLONG_MAX;
        while (tp[x] != tp[y])
        {
            if (dep[tp[x]] < dep[tp[y]])
                swap(x, y);
            ret = min(ret, query(id[tp[x]], id[x]));
            x = p[tp[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        ret = min(ret, query(id[x], id[y]));
        return ret;
    }
};

vector<ll> g[200000 + 1];

void _144()
{
    ll n, q;
    cin >> n >> q;

    HLD hld(n);

    for (ll i = 1; i <= n; i++)
    {
        ll val;
        cin >> val;
        hld.set_value(i, val);
    }

    for (ll i = 0; i < n - 1; i++)
    {
        ll a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    hld.add_edges(g);
    hld.initialize();

    while (q--)
    {
        ll type;
        cin >> type;

        if (type == 1)
        {
            ll s, x;
            cin >> s >> x;
            hld.update_node(s, x);
        }
        else if (type == 2)
        {
            ll a, b;
            cin >> a >> b;
            cout << hld.query_path_min(a, b) << " ";
        }
    }

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
