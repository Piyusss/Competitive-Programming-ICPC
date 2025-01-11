class SegmentTree {
private:
    vector<int> tree;
    vector<int> arr;
    int n;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = start;
        } else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);

            int left = tree[2 * node + 1];
            int right = tree[2 * node + 2];
            tree[node] = (arr[left] <= arr[right]) ? left : right;
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) {
            return -1;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int left = query(2 * node + 1, start, mid, l, r);
        int right = query(2 * node + 2, mid + 1, end, l, r);

        if (left == -1) return right;
        if (right == -1) return left;

        return (arr[left] <= arr[right]) ? left : right;
    }

    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            arr[idx] = value;
            tree[node] = start;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node + 1, start, mid, idx, value);
            } else {
                update(2 * node + 2, mid + 1, end, idx, value);
            }

            int left = tree[2 * node + 1];
            int right = tree[2 * node + 2];
            tree[node] = (arr[left] <= arr[right]) ? left : right;
        }
    }

public:
    SegmentTree(const vector<int>& input) {
        n = input.size();
        arr = input;
        tree.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    void update(int idx, int value) {
        update(0, 0, n - 1, idx, value);
    }
};
