template <typename T>
class PersistentSegmentTree
{
private:
    struct Node
    {
        T val;
        Node *l, *r;

        Node(T x) : val(x), l(nullptr), r(nullptr) {}

        Node(Node *ll, Node *rr)
        {
            l = ll;
            r = rr;
            val = T(0);
            if (l)
                val += l->val;
            if (r)
                val += r->val;
        }

        Node(Node *cp) : val(cp->val), l(cp->l), r(cp->r) {}
    };

    vector<Node *> roots;
    int n;
    vector<T> a;
    int cnt;

    Node *build(int l = 1, int r = -1)
    {
        if (r == -1)
            r = n;
        if (l == r)
            return new Node(a[l]);
        int mid = (l + r) / 2;
        return new Node(build(l, mid), build(mid + 1, r));
    }

    Node *update(Node *node, T val, int pos, int l = 1, int r = -1)
    {
        if (r == -1)
            r = n;
        if (l == r)
            return new Node(val);
        int mid = (l + r) / 2;
        if (pos > mid)
            return new Node(node->l, update(node->r, val, pos, mid + 1, r));
        else
            return new Node(update(node->l, val, pos, l, mid), node->r);
    }

    T query(Node *node, int a, int b, int l = 1, int r = -1)
    {
        if (r == -1)
            r = n;
        if (l > b || r < a)
            return T(0);
        if (l >= a && r <= b)
            return node->val;
        int mid = (l + r) / 2;
        return query(node->l, a, b, l, mid) + query(node->r, a, b, mid + 1, r);
    }

public:
    PersistentSegmentTree(int size) : n(size), cnt(1)
    {
        a.resize(n + 1);
        roots.resize(200001, nullptr);
    }

    void setInitial(int pos, T val)
    {
        a[pos] = val;
    }

    void buildInitial()
    {
        roots[cnt++] = build();
    }

    int update(int version, int pos, T val)
    {
        roots[version] = update(roots[version], val, pos);
        return version;
    }

    T query(int version, int l, int r)
    {
        return query(roots[version], l, r);
    }

    int clone(int version)
    {
        roots[cnt] = new Node(roots[version]);
        return cnt++;
    }
};
