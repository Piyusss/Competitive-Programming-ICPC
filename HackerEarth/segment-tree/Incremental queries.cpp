//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

// for-sum-start
class SegmentTreeSum
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
    SegmentTreeSum(const vector<ll> &input)
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
// for-sum-end

// for-max-start
class SegmentTreeMax
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
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    ll query(ll node, ll start, ll end, ll l, ll r)
    {
        if (r < start || l > end)
        {
            return INT_MIN;
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        ll mid = (start + end) / 2;
        ll left = query(2 * node + 1, start, mid, l, r);
        ll right = query(2 * node + 2, mid + 1, end, l, r);
        return max(left, right);
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
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

public:
    SegmentTreeMax(const vector<ll> &input)
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
// for-max-end

// for-parity-start
class SegmentTreeParity
{
private:
    vector<pair<ll, ll>> tree;
    vector<ll> arr;
    ll n;

    void build(ll node, ll start, ll end)
    {
        if (start == end)
        {
            tree[node].first = (arr[start] & 1) ? 1 : 0;     // odd-count
            tree[node].second = (!(arr[start] & 1)) ? 1 : 0; // even-count
        }
        else
        {
            ll mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node].first = tree[2 * node + 1].first + tree[2 * node + 2].first;
            tree[node].second = tree[2 * node + 1].second + tree[2 * node + 2].second;
        }
    }

    ll query(ll node, ll start, ll end, ll l, ll r, ll checker)
    {
        if (r < start || l > end)
        {
            return 0;
        }
        if (l <= start && end <= r)
        {
            return (checker & 1) ? tree[node].second : tree[node].first;
        }
        ll mid = (start + end) / 2;
        ll left = query(2 * node + 1, start, mid, l, r, checker);
        ll right = query(2 * node + 2, mid + 1, end, l, r, checker);
        return left + right;
    }

    void update(ll node, ll start, ll end, ll idx, ll value)
    {
        if (start == end)
        {
            tree[node].first = (value & 1) ? 1 : 0;     // odd-count
            tree[node].second = (!(value & 1)) ? 1 : 0; // even-count
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
            tree[node].first = tree[node * 2 + 1].first + tree[node * 2 + 2].first;
            tree[node].second = tree[node * 2 + 1].second + tree[node * 2 + 2].second;
        }
    }

public:
    SegmentTreeParity(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n, {0, 0});
        build(0, 0, n - 1);
    }

    ll query(ll l, ll r, ll checker)
    {
        return query(0, 0, n - 1, l, r, checker);
    }

    void update(ll idx, ll value)
    {
        update(0, 0, n - 1, idx, value);
    }
};
// for-parity-end

void _144()
{
    ll n, q;
    cin >> n >> q;

    vector<ll> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    SegmentTreeMax t1(v);
    SegmentTreeSum t2(v);
    SegmentTreeParity t3(v);

    while (q--)
    {
        ll type;
        cin >> type;

        if (type == 1)
        {
            ll l, x;
            cin >> l >> x;
            l--;
            v[l] = x;
            t1.update(l, x);
            t2.update(l, x);
            t3.update(l, x);
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            l--;
            r--;

            ll maxiOfThisRange = t1.query(l, r);
            ll sumOfThisRange = t2.query(l, r);
            ll parityOfThisRange = t3.query(l, r, maxiOfThisRange);

            cout << parityOfThisRange + ((maxiOfThisRange * (r - l + 1)) - sumOfThisRange - parityOfThisRange) / 2 << "\n";
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
