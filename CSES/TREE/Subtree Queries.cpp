//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class SegmentTree
{
private:
    vector<ll> tree;
    vector<ll> arr;
    ll n;

    void build(ll node, ll start, ll end)
    {
        if (start == end)
        {
            tree[node] = arr[start];
        }
        else
        {
            ll mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    ll query(ll node, ll start, ll end, ll l, ll r)
    {
        if (r < start || l > end)
        {
            return 0;
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        ll mid = (start + end) / 2;
        ll left = query(2 * node + 1, start, mid, l, r);
        ll right = query(2 * node + 2, mid + 1, end, l, r);
        return left + right;
    }

    void update(ll node, ll start, ll end, ll idx, ll value)
    {
        if (start == end)
        {
            tree[node] = value;
        }
        else
        {
            ll mid = (start + end) / 2;
            if (idx <= mid)
            {
                update(2 * node + 1, start, mid, idx, value);
            }
            else
            {
                update(2 * node + 2, mid + 1, end, idx, value);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

public:
    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    ll query(ll l, ll r)
    {
        return query(0, 0, n - 1, l, r);
    }

    void update(ll idx, ll value)
    {
        update(0, 0, n - 1, idx, value);
    }
};

vector<ll> g[200000 + 1];
vector<ll> val(200000 + 1, -1);
vector<ll> inTime(200000 + 1);
vector<ll> outTime(200000 + 1);
vector<ll> eulerTour;
ll cnt = 1;

void dfs(ll node, ll p)
{
    inTime[node] = cnt++;
    eulerTour.push_back(val[node]);

    for (auto &c : g[node])
    {
        if (c != p)
        {
            dfs(c, node);
        }
    }

    outTime[node] = cnt++;
    eulerTour.push_back(val[node]);
}

void _144()
{
    ll n, q;
    cin >> n >> q;

    for (ll i = 1; i <= n; i++)
        cin >> val[i];

    for (ll i = 0; i < n - 1; i++)
    {
        ll a, b;
        cin >> a >> b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    eulerTour.push_back(-1);
    dfs(1, -1);
    // for(auto &it:eulerTour) cout<<it<<" ";

    SegmentTree t(eulerTour);
    while (q--)
    {
        ll type;
        cin >> type;

        if (type == 1)
        {
            ll s, x;
            cin >> s >> x;
            // find indexes of both left-s and right-s
            ll leftIdx = inTime[s];
            ll rightIdx = outTime[s];

            t.update(leftIdx, x);
            t.update(rightIdx, x);
        }
        else
        {
            ll s;
            cin >> s;
            // find indexes of both left-s and right-s
            ll leftIdx = inTime[s];
            ll rightIdx = outTime[s];
            cout << t.query(leftIdx, rightIdx) / 2 << "\n";
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
