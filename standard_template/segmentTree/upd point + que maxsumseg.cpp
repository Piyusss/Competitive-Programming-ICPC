struct SegmentTree
{
    struct Node
    {
        ll sum, prefixSum, suffixSum, maxSum;
    };

    vector<Node> tree;
    vector<ll> arr;
    ll n;

    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    void build(ll node, ll start, ll end)
    {
        if (start == end)
        {
            tree[node] = {arr[start], max(0LL, arr[start]), max(0LL, arr[start]), max(0LL, arr[start])};
        }
        else
        {
            ll mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            merge(node);
        }
    }

    void merge(ll node)
    {
        ll left = 2 * node + 1, right = 2 * node + 2;
        tree[node].sum = tree[left].sum + tree[right].sum;
        tree[node].prefixSum = max(tree[left].prefixSum, tree[left].sum + tree[right].prefixSum);
        tree[node].suffixSum = max(tree[right].suffixSum, tree[right].sum + tree[left].suffixSum);
        tree[node].maxSum = max({tree[left].maxSum, tree[right].maxSum, tree[left].suffixSum + tree[right].prefixSum});
    }

    void update(ll node, ll start, ll end, ll idx, ll value)
    {
        if (start == end)
        {
            arr[idx] = value;
            tree[node] = {arr[start], max(0LL, arr[start]), max(0LL, arr[start]), max(0LL, arr[start])};
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
            merge(node);
        }
    }

    Node query(ll node, ll start, ll end, ll l, ll r)
    {
        if (r < start || end < l)
        {
            return {0, 0, 0, 0};
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        ll mid = (start + end) / 2;
        Node left = query(2 * node + 1, start, mid, l, r);
        Node right = query(2 * node + 2, mid + 1, end, l, r);
        Node result;
        result.sum = left.sum + right.sum;
        result.prefixSum = max(left.prefixSum, left.sum + right.prefixSum);
        result.suffixSum = max(right.suffixSum, right.sum + left.suffixSum);
        result.maxSum = max({left.maxSum, right.maxSum, left.suffixSum + right.prefixSum});
        return result;
    }

    void update(ll idx, ll value)
    {
        update(0, 0, n - 1, idx, value);
    }

    ll query(ll l, ll r)
    {
        return query(0, 0, n - 1, l, r).maxSum;
    }
};
