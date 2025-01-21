#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
const int N = 500050;

struct persistent_dsu
{
    struct state
    {
        int u, v, rnku, rnkv;
        state() : u(-1), v(-1), rnku(-1), rnkv(-1) {}
        state(int _u, int _rnku, int _v, int _rnkv) : u(_u), rnku(_rnku), v(_v), rnkv(_rnkv) {}
    };

    stack<state> st;
    int par[N], depth[N];
    int comp;

    persistent_dsu()
    {
        comp = 0;
        memset(par, -1, sizeof(par));
        memset(depth, 0, sizeof(depth));
    }

    void init(int n)
    {
        comp = n;
        for (int i = 0; i <= n; i++)
        {
            par[i] = i;
            depth[i] = 1;
        }
    }

    int root(int x)
    {
        if (x == par[x])
            return x;
        return root(par[x]);
    }

    void unite(int x, int y)
    {
        int rx = root(x), ry = root(y);
        if (rx == ry)
        {
            st.push(state());
            return;
        }
        if (depth[rx] < depth[ry])
        {
            par[rx] = ry;
        }
        else if (depth[ry] < depth[rx])
        {
            par[ry] = rx;
        }
        else
        {
            par[rx] = ry;
            depth[rx]++;
        }
        comp--;
        st.push(state(rx, depth[rx], ry, depth[ry]));
    }

    void backtrack(int c)
    {
        while (!st.empty() && c)
        {
            if (st.top().u == -1)
            {
                st.pop();
                c--;
                continue;
            }
            par[st.top().u] = st.top().u;
            par[st.top().v] = st.top().v;
            depth[st.top().u] = st.top().rnku;
            depth[st.top().v] = st.top().rnkv;
            st.pop();
            c--;
            comp++;
        }
    }
};

vector<pair<int, int>> alive[4 * N];
persistent_dsu d;
int ans[N];

void upd(int n, int b, int e, int i, int j, pair<int, int> &p)
{
    if (b > j || e < i)
        return;
    if (b >= i && e <= j)
    {
        alive[n].push_back(p);
        return;
    }
    int mid = (b + e) / 2;
    upd(2 * n, b, mid, i, j, p);
    upd(2 * n + 1, mid + 1, e, i, j, p);
}

void query(int n, int b, int e)
{
    if (b > e)
        return;

    int prevsz = d.st.size();
    for (auto p : alive[n])
    {
        d.unite(p.first, p.second);
    }

    if (b == e)
    {
        ans[b] = d.comp;
        d.backtrack(d.st.size() - prevsz);
        return;
    }

    int mid = (b + e) / 2;
    query(2 * n, b, mid);
    query(2 * n + 1, mid + 1, e);
    d.backtrack(d.st.size() - prevsz);
}

void processQueries(int n, int m, vector<tuple<char, int, int>> &operations)
{
    vector<bool> isquery(m + 1, false);
    map<pair<int, int>, int> edge_time;
    set<pair<int, int>> active_edges;

    for (int i = 1; i <= m; i++)
    {
        char type;
        int u = 0, v = 0;
        tie(type, u, v) = operations[i - 1];

        if (type == '?')
        {
            isquery[i] = true;
        }
        else if (type == '+')
        {
            if (u > v)
                swap(u, v);
            pair<int, int> p = {u, v};
            active_edges.insert(p);
            edge_time[p] = i;
        }
        else if (type == '-')
        {
            if (u > v)
                swap(u, v);
            pair<int, int> p = {u, v};
            active_edges.erase(p);
            upd(1, 1, m, edge_time[p], i - 1, p);
        }
    }

    for (auto p : active_edges)
    {
        upd(1, 1, m, edge_time[p], m, p);
    }

    query(1, 1, m);

    for (int i = 1; i <= m; i++)
    {
        if (isquery[i])
        {
            cout << ans[i] << '\n';
        }
    }
}

void _144()
{
    int n, m;
    cin >> n >> m;

    vector<tuple<char, int, int>> operations(m);
    for (int i = 0; i < m; i++)
    {
        char type;
        int u = 0, v = 0;
        cin >> type;
        if (type != '?')
            cin >> u >> v;
        operations[i] = {type, u, v};
    }

    d.init(n);
    processQueries(n, m, operations);
}

//--------------------------------END--------------------------------------------------

// Main
int main()

{   freopen("connect.in", "r",stdin);
    freopen("connect.out", "w", stdout);

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
