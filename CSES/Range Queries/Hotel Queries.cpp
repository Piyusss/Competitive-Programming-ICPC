//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class SegmentTree
{
private:
    vector<ll> tree;
    vector<ll> arr;
    ll n;

    void build(ll node, ll start, ll end)
    {
        if (start == end)
        {
            tree[node] = arr[start];
        }
        else
        {
            ll mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void update(ll node, ll start, ll end, ll idx, ll value)
    {
        if (start == end)
        {
            tree[node] = value;
            arr[start] = value;
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
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    ll first_above(ll node, ll start, ll end, ll x, ll l)
    {
        if (tree[node] < x || end < l)
        {
            return -1;
        }
        if (start == end)
        {
            return start;
        }
        ll mid = (start + end) / 2;
        if (mid >= l && tree[2 * node + 1] >= x)
        {
            ll left_result = first_above(2 * node + 1, start, mid, x, l);
            if (left_result != -1)
                return left_result;
        }
        return first_above(2 * node + 2, mid + 1, end, x, l);
    }

public:
    SegmentTree(const vector<ll> &input)
    {
        n = input.size();
        arr = input;
        tree.resize(4 * n, 0);
        build(0, 0, n - 1);
    }

    void set(ll idx, ll value)
    {
        update(0, 0, n - 1, idx, value);
    }

    ll first_above(ll x, ll l)
    {
        return first_above(0, 0, n - 1, x, l);
    }
};

void _144()
{
    ll n,m;
    cin>>n>>m;

    vector<ll>free_rooms(n),group_need(m);

    for(int i=0;i<n;i++) cin>>free_rooms[i];
    for(int i=0;i<m;i++) cin>>group_need[i];

    SegmentTree t(free_rooms);

    for(auto &it:group_need){
        ll res=t.first_above(it,0);
        if(res==-1){
            cout<<"0"<<" ";
        }
        else{
            cout<<res+1<<" ";
            free_rooms[res]-=it;
            t.set(res,free_rooms[res]);
        }
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
