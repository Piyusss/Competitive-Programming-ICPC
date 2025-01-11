//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class SegmentTree
{
private:
    struct Node
    {
        ll sum, maxPrefixSum;
    };
    vector<Node> tree;
    vector<ll> arr;
    ll n;

    void build(ll node, ll start, ll end)
    {
        if (start == end)
        {
            tree[node] = {arr[start], max((ll)0, arr[start])};
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
        tree[node].sum = tree[2 * node + 1].sum + tree[2 * node + 2].sum;
        tree[node].maxPrefixSum = max(tree[2 * node + 1].maxPrefixSum,
                                      tree[2 * node + 1].sum + tree[2 * node + 2].maxPrefixSum);
    }

    void update(ll node, ll start, ll end, ll idx, ll value)
    {
        if (start == end)
        {
            tree[node] = {value, max((ll)0, value)};
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
        if (r < start || l > end)
        {
            return {0, 0};
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        ll mid = (start + end) / 2;
        Node left = query(2 * node + 1, start, mid, l, r);
        Node right = query(2 * node + 2, mid + 1, end, l, r);
        return {left.sum + right.sum, max(left.maxPrefixSum, left.sum + right.maxPrefixSum)};
    }

public:
    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n, {0, 0});
        build(0, 0, n - 1);
    }

    void update(ll idx, ll value)
    {
        update(0, 0, n - 1, idx, value);
    }

    ll query(ll l, ll r)
    {
        return query(0, 0, n - 1, l, r).maxPrefixSum;
    }
};

void _144()
{
    ll n,q;
    cin>>n>>q;

    vector<ll>v(n);
    for(int i=0;i<n;i++) cin>>v[i];

    SegmentTree t(v);

    while(q--){
        ll a, b, c;
        cin >> a >> b >> c;

        if (a == 1)
        {
            b -= 1;
            t.update(b, c);
        }
        else
        {
            b -= 1;
            c -= 1;
            cout << t.query(b, c) << "\n";
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
