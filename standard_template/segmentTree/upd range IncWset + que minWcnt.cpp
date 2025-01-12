#include <iostream>
#include <vector>
#include <climits>

using namespace std;

enum QueryType
{
    ADD,
    SET,
    NONE
};

struct Tag
{
    QueryType type = NONE;
    long long val = 0;

    void apply(const Tag &t)
    {
        if (t.type == ADD)
        {
            val += t.val;
            if (type != SET)
            {
                type = ADD;
            }
        }
        else if (t.type == SET)
        {
            type = SET;
            val = t.val;
        }
    }
};

struct Info
{
    long long minVal = INT_MAX;
    long long count = 0;

    void apply(const Tag &t, int l, int r)
    {
        if (t.type == SET)
        {
            minVal = t.val;
            count = r - l + 1;
        }
        else if (t.type == ADD)
        {
            minVal += t.val;
        }
    }
};

Info operator+(const Info &a, const Info &b)
{
    if (a.minVal < b.minVal)
    {
        return a;
    }
    else if (a.minVal > b.minVal)
    {
        return b;
    }
    else
    {
        return {a.minVal, a.count + b.count};
    }
}

class SegmentTree
{
private:
    vector<Info> tree;
    vector<Tag> lazy;
    vector<long long> arr;
    long long n;

    void build(int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = {arr[start], 1};
        }
        else
        {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void apply(int node, int start, int end, const Tag &x)
    {
        tree[node].apply(x, start, end);
        lazy[node].apply(x);
    }

    void push_down(int node, int start, int end)
    {
        int mid = (start + end) / 2;
        apply(2 * node + 1, start, mid, lazy[node]);
        apply(2 * node + 2, mid + 1, end, lazy[node]);
        lazy[node] = Tag();
    }

    void update(int node, int start, int end, int l, int r, const Tag &x)
    {
        if (r < start || l > end)
        {
            return;
        }
        if (l <= start && end <= r)
        {
            apply(node, start, end, x);
        }
        else
        {
            push_down(node, start, end);
            int mid = (start + end) / 2;
            update(2 * node + 1, start, mid, l, r, x);
            update(2 * node + 2, mid + 1, end, l, r, x);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    Info query(int node, int start, int end, int l, int r)
    {
        if (r < start || l > end)
        {
            return Info();
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        push_down(node, start, end);
        int mid = (start + end) / 2;
        return query(2 * node + 1, start, mid, l, r) + query(2 * node + 2, mid + 1, end, l, r);
    }

public:
    SegmentTree(const vector<long long> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n);
        lazy.resize(4 * n);
        build(0, 0, n - 1);
    }

    void update(int l, int r, QueryType type, long long value)
    {
        Tag tag;
        tag.type = type;
        tag.val = value;
        update(0, 0, n - 1, l, r, tag);
    }

    Info query(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }
};

int main()
{
    int n, q;
    cin >> n >> q;
    vector<long long> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    SegmentTree segmentTree(arr);

    for (int i = 0; i < q; ++i)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r, x;
            cin >> l >> r >> x;
            segmentTree.update(l - 1, r - 1, ADD, x);
        }
        else if (type == 2)
        {
            int l, r, x;
            cin >> l >> r >> x;
            segmentTree.update(l - 1, r - 1, SET, x);
        }
        else if (type == 3)
        {
            int l, r;
            cin >> l >> r;
            Info result = segmentTree.query(l - 1, r - 1);
            cout << result.minVal << " " << result.count << endl;
        }
    }

    return 0;
}
