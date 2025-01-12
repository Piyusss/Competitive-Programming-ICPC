//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class SegmentTree
{
private:
    class Node
    {
    public:
        ll sum, maxPrefixSum, maxSuffixSum, maxSum;

        Node() : sum(0), maxPrefixSum(0), maxSuffixSum(0), maxSum(0) {}

        Node(ll sum, ll maxPrefixSum, ll maxSuffixSum, ll maxSum)
            : sum(sum), maxPrefixSum(maxPrefixSum), maxSuffixSum(maxSuffixSum), maxSum(maxSum) {}
    };

    vector<Node> tree;
    vector<ll> arr;
    ll n;

    void build(ll node, ll start, ll end)
    {
        if (start == end)
        {
            tree[node] = Node(arr[start], max(0LL, arr[start]), max(0LL, arr[start]), max(0LL, arr[start]));
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
        tree[node].maxPrefixSum = max(tree[left].maxPrefixSum, tree[left].sum + tree[right].maxPrefixSum);
        tree[node].maxSuffixSum = max(tree[right].maxSuffixSum, tree[right].sum + tree[left].maxSuffixSum);
        tree[node].maxSum = max({tree[left].maxSum, tree[right].maxSum, tree[left].maxSuffixSum + tree[right].maxPrefixSum});
    }

    void update(ll node, ll start, ll end, ll idx, ll value)
    {
        if (start == end)
        {
            arr[idx] = value;
            tree[node] = Node(arr[start], max(0LL, arr[start]), max(0LL, arr[start]), max(0LL, arr[start]));
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
            return Node(0, 0, 0, 0); // Return an invalid node
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
        result.maxPrefixSum = max(left.maxPrefixSum, left.sum + right.maxPrefixSum);
        result.maxSuffixSum = max(right.maxSuffixSum, right.sum + left.maxSuffixSum);
        result.maxSum = max({left.maxSum, right.maxSum, left.maxSuffixSum + right.maxPrefixSum});
        return result;
    }

public:
    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n);
        build(0, 0, n - 1);
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

void _144()
{
    ll n, m;
    cin >> n >> m;

    vector<ll> arr(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    SegmentTree t(arr);
    cout << t.query(0, n - 1) << "\n";

    while (m--)
    {
        ll i, v;
        cin >> i >> v;
        t.update(i, v);
        cout << t.query(0, n - 1) << "\n";
    }
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
//freopen("input.in", "r",stdin);
//freopen("output.out", "w",stdout);

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
