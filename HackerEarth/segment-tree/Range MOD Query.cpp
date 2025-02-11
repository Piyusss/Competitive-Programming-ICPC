//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1E9 + 7;
//--------------------------------WRITE_HERE-------------------------------------------

class SegmentTree
{
private:
    vector<ll> tree;
    vector<ll> arr;
    vector<ll> power;
    ll n;

    void build(ll node, ll start, ll end)
    {
        if (start == end)
        {
            tree[node] = arr[start] % MOD;
        }
        else
        {
            ll mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = ((tree[2 * node + 1] % MOD) * (power[end - mid] % MOD)) + (tree[2 * node + 2] % MOD);
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
            return tree[node] % MOD;
        }
        ll mid = (start + end) / 2;
        ll left = query(2 * node + 1, start, mid, l, r);
        ll right = query(2 * node + 2, mid + 1, end, l, r);
        return ((left % MOD) * (power[max((ll)0, min(end, r) - mid)] % MOD)) + (right % MOD);
    }

    void update(ll node, ll start, ll end, ll idx)
    {
        if (start == end)
        {
            tree[node] ^= 1;
        }
        else
        {
            ll mid = (start + end) / 2;
            if (idx <= mid)
            {
                update(2 * node + 1, start, mid, idx);
            }
            else
            {
                update(2 * node + 2, mid + 1, end, idx);
            }
            tree[node] = ((tree[2 * node + 1] % MOD) * (power[end - mid] % MOD)) + (tree[2 * node + 2] % MOD);
        }
    }

public:
    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        power.resize(n + 1, 1);
        for (ll i = 1; i <= n; i++)
            power[i] = (power[i - 1] * 2) % MOD;
        arr = input;
        tree.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    ll query(ll l, ll r)
    {
        return query(0, 0, n - 1, l, r) % MOD;
    }

    void update(ll idx)
    {
        update(0, 0, n - 1, idx);
    }
};

void _144()
{
    ll n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
        v[i] = s[i] - '0';

    SegmentTree t(v);

    while (q--)
    {
        ll type;
        cin >> type;

        if (type == 1)
        {
            ll idx;
            cin >> idx;
            idx--;
            v[idx] ^= 1;
            t.update(idx);
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << t.query(l, r) % MOD << "\n";
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
