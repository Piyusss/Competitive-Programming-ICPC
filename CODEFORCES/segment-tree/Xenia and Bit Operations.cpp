//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class SegmentTree
{
private:
    vector<int> level;
    vector<int> tree;
    vector<int> arr;
    int n;

    void build(int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = arr[start];
            level[node] = 1;
        }
        else
        {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            level[node] = level[2 * node + 1] + 1;
            tree[node] = (!(level[node] & 1)) ? (tree[2 * node + 1] | tree[2 * node + 2]) : (tree[2 * node + 1] ^ tree[2 * node + 2]);
        }
    }

    int query(int node, int start, int end, int l, int r)
    {
        if (r < start || l > end)
        {
            return 0;
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left = query(2 * node + 1, start, mid, l, r);
        int right = query(2 * node + 2, mid + 1, end, l, r);

        return (!(level[node] & 1)) ? (left | right) : (left ^ right);
    }

    void update(int node, int start, int end, int idx, int value)
    {
        if (start == end)
        {
            tree[node] = value;
        }
        else
        {
            int mid = (start + end) / 2;
            if (idx <= mid)
            {
                update(2 * node + 1, start, mid, idx, value);
            }
            else
            {
                update(2 * node + 2, mid + 1, end, idx, value);
            }

            tree[node] = (!(level[node] & 1)) ? (tree[2 * node + 1] | tree[2 * node + 2]) : (tree[2 * node + 1] ^ tree[2 * node + 2]);
        }
    }

public:
    SegmentTree(const vector<int> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n, 0);
        level.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    int query(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }

    void update(int idx, int value)
    {
        update(0, 0, n - 1, idx, value);
    }
};

void _144()
{
    int n, m;
    cin >> n >> m;

    vector<int> seq(1 << n, 0);

    for (int i = 0; i < (1 << n); i++)
    {
        int x;
        cin >> x;
        seq[i] = x;
    }

    SegmentTree t(seq);

    for (int i = 0; i < m; i++)
    {
        int p, b;
        cin >> p >> b;
        p--;

        t.update(p, b);
        cout << t.query(0, (1 << n) - 1) << "\n";
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
