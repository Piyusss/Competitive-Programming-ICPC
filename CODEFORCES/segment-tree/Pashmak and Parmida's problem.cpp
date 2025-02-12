//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class SegmentTree
{
private:
    vector<ll> tree;
    ll n;

    void build(ll node, ll start, ll end)
    {
        if (start == end)
        {
            tree[node] = 0;
        }
        else
        {
            ll mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    ll query(ll node, ll start, ll end, ll l, ll r)
    {
        if (r < start || l > end)
        {
            return 0;
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }

        ll mid = (start + end) / 2;
        ll left = query(2 * node + 1, start, mid, l, r);
        ll right = query(2 * node + 2, mid + 1, end, l, r);

        return left + right;
    }

    void update(ll node, ll start, ll end, ll idx, ll delta)
    {
        if (start == end)
        {
            tree[node] += delta;
        }
        else
        {
            ll mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node + 1, start, mid, idx, delta);
            else
                update(2 * node + 2, mid + 1, end, idx, delta);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

public:
    SegmentTree(ll maxi)
    {
        maxi += 1;
        n = maxi;
        tree.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    ll query(ll l, ll r)
    {
        return query(0, 0, n - 1, l, r);
    }

    void update(ll idx, ll delta)
    {
        update(0, 0, n - 1, idx, delta);
    }
};

void _144()
{
    ll n;
    cin >> n;

    vector<ll> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    // Coordinate-Compression-Start (since a[i] can go upto 1E9)
    vector<ll> comp = v;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    for (int i = 0; i < n; i++)
    {
        v[i] = lower_bound(comp.begin(), comp.end(), v[i]) - comp.begin();
    }
    // Coordinate-Compression-End

    ll maxi = comp.size() - 1;

    // just-do-same-as-before-now
    SegmentTree tForw(maxi);
    SegmentTree tBack(maxi);

    vector<ll> starting(n), ending(n);

    for (int i = 0; i < n; i++)
        tBack.update(v[i], 1);

    for (int j = 0; j < n; j++)
    {
        tForw.update(v[j], 1);
        tBack.update(v[j], -1);

        // if (j == 0 || j == n - 1)
        //     continue;

        ll greatLeft = tForw.query(v[j] + 1, maxi);
        ll smallLeft = tForw.query(0, v[j] - 1);
        ll equalOnLeft = j + 1 - greatLeft - smallLeft;
        starting[j] = equalOnLeft;

        ll smallRight = tBack.query(0, v[j] - 1);
        ll greatRight = tBack.query(v[j] + 1, maxi);
        ll equalOnRight = n - j - smallRight - greatRight;
        ending[j] = equalOnRight;
    }

    // for(int i=0;i<n;i++) cout<<starting[i]<<" ";
    // cout<<"\n";
    // for(int i=0;i<n;i++) cout<<ending[i]<<" ";
    // cout<<"\n";

    SegmentTree final(*max_element(ending.begin(), ending.end()));

    for (int i = 0; i < n; i++)
        final.update(ending[i], 1);

    ll cnt = 0;
    for (int i = 0; i < n; i++)
    {
        final.update(ending[i], -1);

        if (i == 0)
            continue;
        ll smallOnRight = final.query(0, starting[i] - 1);

        cnt += smallOnRight;
    }

    cout << cnt;
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
