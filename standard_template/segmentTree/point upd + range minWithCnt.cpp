class SegmentTree
{
private:
    vector<pair<ll, ll>> tree;
    vector<ll> arr;
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
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        ll mid = (start + end) / 2;
        pair<ll, ll> left = query(2 * node + 1, start, mid, l, r);
        pair<ll, ll> right = query(2 * node + 2, mid + 1, end, l, r);
        return merge(left, right);
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

    void update(ll node, ll start, ll end, ll idx, ll value)
    {
        if (start == end)
        {
            arr[start] = value;
            tree[node] = {value, 1};
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
            tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

public:
    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n, {INT_MAX, 0});
        build(0, 0, n - 1);
    }

    pair<ll, ll> query(ll l, ll r)
    {
        return query(0, 0, n - 1, l, r);
    }

    void update(ll idx, ll value)
    {
        update(0, 0, n - 1, idx, value);
    }
};
