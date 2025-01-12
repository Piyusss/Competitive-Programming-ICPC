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

    void update(ll node, ll start, ll end, ll idx, ll value)
    {
        if (start == end)
        {
            tree[node] = value;
            arr[start] = value;
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

    ll query(ll node, ll start, ll end, ll k)
    {
        if (start == end)
        {
            return start;
        }
        ll mid = (start + end) / 2;
        if (tree[2 * node + 1] >= k)
        {
            return query(2 * node + 1, start, mid, k);
        }
        else
        {
            return query(2 * node + 2, mid + 1, end, k - tree[2 * node + 1]);
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

    void update(ll idx, ll value)
    {
        update(0, 0, n - 1, idx, value);
    }

    ll query(ll k)
    {
        return query(0, 0, n - 1, k);
    }
};
