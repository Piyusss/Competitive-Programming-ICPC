class SegmentTree
{
private:
    vector<pair<ll, ll>> tree;
    vector<ll> arr, lazy;
    ll n;

    void build(ll node, ll start, ll end)
    {
        if (start == end)
        {
            tree[node] = {arr[start], 1};
        }
        else
        {
            ll mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    pair<ll, ll> query(ll node, ll start, ll end, ll l, ll r)
    {
        if (r < start || l > end)
        {
            return {INT_MAX, 0};
        }
        propagate(node, start, end);
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        ll mid = (start + end) / 2;
        pair<ll, ll> left = query(2 * node + 1, start, mid, l, r);
        pair<ll, ll> right = query(2 * node + 2, mid + 1, end, l, r);
        return merge(left, right);
    }

    void update(ll node, ll start, ll end, ll l, ll r, ll value)
    {
        if (r < start || l > end)
        {
            return;
        }
        propagate(node, start, end);
        if (l <= start && end <= r)
        {
            tree[node] = {tree[node].first + value, tree[node].second};
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
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void propagate(ll node, ll start, ll end)
    {
        if (lazy[node] != 0)
        {
            tree[node].first += lazy[node];
            if (start != end)
            {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    pair<ll, ll> merge(pair<ll, ll> left, pair<ll, ll> right)
    {
        if (left.first < right.first)
        {
            return left;
        }
        else if (left.first > right.first)
        {
            return right;
        }
        else
        {
            return {left.first, left.second + right.second};
        }
    }

public:
    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n, {INT_MAX, 0});
        lazy.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    pair<ll, ll> query(ll l, ll r)
    {
        return query(0, 0, n - 1, l, r);
    }

    void update(ll l, ll r, ll value)
    {
        update(0, 0, n - 1, l, r, value);
    }
};
