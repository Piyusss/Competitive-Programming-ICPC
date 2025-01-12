template <class Info, class Tag>
class LazySegtreeDouble
{
private:
    const int n;
    vector<Info> tree;
    vector<Tag> lazy;

    void build(int v, int l, int r, const vector<Info> &a)
    {
        if (l == r)
        {
            tree[v] = a[l];
        }
        else
        {
            int m = (l + r) / 2;
            build(2 * v, l, m, a);
            build(2 * v + 1, m + 1, r, a);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    void apply(int v, int l, int r, const Tag &x)
    {
        tree[v].apply(x, l, r);
        lazy[v].apply(x);
    }

    void push_down(int v, int l, int r)
    {
        int m = (l + r) / 2;
        apply(2 * v, l, m, lazy[v]);
        apply(2 * v + 1, m + 1, r, lazy[v]);
        lazy[v] = Tag();
    }

    void update(int v, int l, int r, int ql, int qr, const Tag &x)
    {
        if (qr < l || ql > r)
        {
            return;
        }
        if (ql <= l && r <= qr)
        {
            apply(v, l, r, x);
        }
        else
        {
            push_down(v, l, r);
            int m = (l + r) / 2;
            update(2 * v, l, m, ql, qr, x);
            update(2 * v + 1, m + 1, r, ql, qr, x);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    Info query(int v, int l, int r, int ql, int qr)
    {
        if (qr < l || ql > r)
        {
            return Info();
        }
        if (l >= ql && r <= qr)
        {
            return tree[v];
        }
        push_down(v, l, r);
        int m = (l + r) / 2;
        return query(2 * v, l, m, ql, qr) +
               query(2 * v + 1, m + 1, r, ql, qr);
    }

public:
    LazySegtreeDouble(int n) : n(n)
    {
        tree.assign(4 << __lg(n), Info());
        lazy.assign(4 << __lg(n), Tag());
    }

    LazySegtreeDouble(const vector<Info> &a) : n(a.size())
    {
        tree.assign(4 << __lg(n), Info());
        lazy.assign(4 << __lg(n), Tag());
        build(1, 0, n - 1, a);
    }

    void update(int ql, int qr, const Tag &x)
    {
        update(1, 0, n - 1, ql, qr, x);
    }

    Info query(int ql, int qr) { return query(1, 0, n - 1, ql, qr); }
};

enum QueryType
{
    ADD,
    SET,
    NONE
};

struct Tag
{
    QueryType type = NONE;
    ll val = 0;
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
    ll sum = 0;
    void apply(const Tag &t, int l, int r)
    {
        if (t.type == SET)
        {
            sum = t.val * (r - l + 1);
        }
        else if (t.type == ADD)
        {
            sum += t.val * (r - l + 1);
        }
    }
};

Info operator+(const Info &a, const Info &b) { return {a.sum + b.sum}; }
