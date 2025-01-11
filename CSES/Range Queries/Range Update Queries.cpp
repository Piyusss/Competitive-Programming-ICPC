//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
class SegmentTree
{
private:
    vector<ll> tree;
    vector<ll> lazy;
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

    void propagate(ll node, ll start, ll end)
    {
        if (lazy[node] != 0)
        {
            tree[node] += (end - start + 1) * lazy[node];

            if (start != end)
            {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }

            lazy[node] = 0;
        }
    }

    ll query(ll node, ll start, ll end, ll l, ll r)
    {
        propagate(node, start, end);

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

    int qwerty(int node, int start, int end, int index)
    {
        propagate(node, start, end);

        if (start == end)
        {
            return tree[node];
        }

        int mid = (start + end) / 2;
        if (index <= mid)
        {
            return qwerty(2 * node + 1, start, mid, index);
        }
        else
        {
            return qwerty(2 * node + 2, mid + 1, end, index);
        }
    }

    void update(ll node, ll start, ll end, ll l, ll r, ll value)
    {
        propagate(node, start, end);

        if (r < start || l > end)
        {
            return;
        }

        if (l <= start && end <= r)
        {
            tree[node] += (end - start + 1) * value;

            if (start != end)
            {
                lazy[2 * node + 1] += value;
                lazy[2 * node + 2] += value;
            }
            return;
        }

        ll mid = (start + end) / 2;
        update(2 * node + 1, start, mid, l, r, value);
        update(2 * node + 2, mid + 1, end, l, r, value);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

public:
    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    ll query(ll l, ll r)
    {
        return query(0, 0, n - 1, l, r);
    }

    void update(ll l, ll r, ll value)
    {
        update(0, 0, n - 1, l, r, value);
    }

    ll qwerty(ll idx)
    {
        return query(0, 0, n - 1, idx, idx);
    }
};

void _144()
{
    ll n, q;
    cin >> n >> q;

    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
        cin >> v[i];

    SegmentTree t(v);

    while (q--)
    {
        ll a;cin>>a;

        if(a==1){
            ll x,y,z;cin>>x>>y>>z;
            x-=1;y-=1;
            t.update(x,y,z);
        }
        else{
            ll k;cin>>k;
            k-=1;
            cout<<t.qwerty(k)<<"\n";
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
