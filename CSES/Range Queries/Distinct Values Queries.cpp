//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class SegmentTreeDistinct
{
private:
    vector<int> segTree;
    unordered_map<int, int> lastOccurrence;
    int n;

    int query(int i, int j, int p, int l, int r)
    {
        if (i > j)
            return 0;
        if (l >= i && r <= j)
            return segTree[p];
        int mid = (l + r) / 2;
        int left = query(i, min(j, mid), 2 * p, l, mid);
        int right = query(max(i, mid + 1), j, 2 * p + 1, mid + 1, r);
        return left + right;
    }

    void update(int x, int val, int p, int l, int r)
    {
        if (l == r)
        {
            segTree[p] += val;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid)
            update(x, val, 2 * p, l, mid);
        else
            update(x, val, 2 * p + 1, mid + 1, r);
        segTree[p] = segTree[2 * p] + segTree[2 * p + 1];
    }

public:
    SegmentTreeDistinct(int size) : n(size)
    {
        segTree.resize(8 * size, 0);
    }

    vector<int> processQueries(vector<int> &arr, vector<pair<int, int>> &queries)
    {
        int cur = n - 1;
        vector<int> ans(queries.size());
        vector<pair<pair<int, int>, int>> indexedQueries;

        for (int i = 0; i < queries.size(); ++i)
        {
            indexedQueries.push_back({{queries[i].first, queries[i].second}, i});
        }

        sort(indexedQueries.begin(), indexedQueries.end(), [](auto &a, auto &b)
             { return a.first.first > b.first.first; });

        for (auto &q : indexedQueries)
        {
            int x = q.first.first, y = q.first.second, idx = q.second;
            while (cur >= x)
            {
                if (lastOccurrence.count(arr[cur]))
                {
                    update(lastOccurrence[arr[cur]], -1, 1, 0, n - 1);
                }
                lastOccurrence[arr[cur]] = cur;
                update(cur, 1, 1, 0, n - 1);
                --cur;
            }
            ans[idx] = query(x, y, 1, 0, n - 1);
        }

        return ans;
    }
};

void _144()
{
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        queries[i] = {x - 1, y - 1};
    }

    SegmentTreeDistinct st(n);
    vector<int> result = st.processQueries(arr, queries);

    for (int &ans : result)
    {
        cout << ans << "\n";
    }

    return;
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
