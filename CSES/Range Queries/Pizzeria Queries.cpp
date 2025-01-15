//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class SegmentTree
{
private:
    vector<int> tree;
    vector<int> arr;
    int n;

    int U = 1e9;

    void build(int node, int start, int end, bool isDown)
    {
        if (start == end)
        {
            tree[node] = isDown ? arr[start] - start - 1 : arr[start] + start + 1;
        }
        else
        {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid, isDown);
            build(2 * node + 2, mid + 1, end, isDown);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    int query(int node, int start, int end, int l, int r)
    {
        if (r < start || l > end)
        {
            return U;
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left = query(2 * node + 1, start, mid, l, r);
        int right = query(2 * node + 2, mid + 1, end, l, r);
        return min(left, right);
    }

    void update(int node, int start, int end, int idx, int value, bool isDown)
    {
        if (start == end)
        {
            tree[node] = isDown ? value - start - 1 : value + start + 1;
        }
        else
        {
            int mid = (start + end) / 2;
            if (idx <= mid)
            {
                update(2 * node + 1, start, mid, idx, value, isDown);
            }
            else
            {
                update(2 * node + 2, mid + 1, end, idx, value, isDown);
            }
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

public:
    SegmentTree(int size, const vector<int> &input, bool isDown)
    {
        n = size;
        arr = input;
        tree.resize(4 * n, U);
        build(0, 0, n - 1, isDown);
    }

    int query(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }

    void update(int idx, int value, bool isDown)
    {
        update(0, 0, n - 1, idx, value, isDown);
    }
};

void _144()
{
    ll n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    SegmentTree down(n, v, 1);
    SegmentTree up(n, v, 0);

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int k, x;
            cin >> k >> x;
            v[k - 1] = x;
            down.update(k - 1, x, 1);
            up.update(k - 1, x, 0);
        }
        else
        {
            int k;
            cin >> k;
            ll d = down.query(0, k - 1) + k;
            ll u = up.query(k - 1, n - 1) - k;
            cout << min(d, u) << "\n";
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
