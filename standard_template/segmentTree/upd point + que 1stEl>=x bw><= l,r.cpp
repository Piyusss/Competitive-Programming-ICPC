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
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
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
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    ll first_above(ll node, ll start, ll end, ll x, ll l, ll r)
    {
        if (tree[node] < x || end < l || start > r)
        {
            return -1;
        }
        if (start == end)
        {
            return start;
        }
        ll mid = (start + end) / 2;
        if (mid >= l && tree[2 * node + 1] >= x)
        {
            ll left_result = first_above(2 * node + 1, start, mid, x, l, r);
            if (left_result != -1)
                return left_result;
        }
        return first_above(2 * node + 2, mid + 1, end, x, l, r);
    }

public:
    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    void set(ll idx, ll value)
    {
        update(0, 0, n - 1, idx, value);
    }

    ll first_above(ll x, ll l, ll r)
    {
        return first_above(0, 0, n - 1, x, l, r);
    }
};
