//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
int n, k, a, b;
vector<int> g[200000 + 1];
vector<int> subtree_size(200000 + 1);
vector<int> processed(200000 + 1);
int cnt[200001]{1}, max_depth;
ll res = 0;

void get_cnt(int node, int p, bool filling, int depth = 1)
{
    if (depth > k)
        return;

    max_depth = max(max_depth, depth);
    if (filling)
        cnt[depth]++;
    else
        res += cnt[k - depth];

    for (int &i : g[node])
    {
        if (!processed[i] && i != p)
        {
            get_cnt(i, node, filling, depth + 1);
        }
    }
}

int get_subtree_size(int node, int p)
{
    subtree_size[node] = 1;
    for (int &c : g[node])
    {
        if (c != p && !processed[c])
        {
            subtree_size[node] += get_subtree_size(c, node);
            ;
        }
    }

    return subtree_size[node];
}

int centroidDfs(int node, int p, int desired)
{
    for (int &c : g[node])
    {
        if (c != p && !processed[c])
        {
            if (subtree_size[c] >= desired)
            {
                return centroidDfs(c, node, desired);
            }
        }
    }

    return node;
}

void centroid_decomposition(int node)
{
    int centroid = centroidDfs(node, -1, get_subtree_size(node, -1) >> 1);
    processed[centroid] = 1;
    max_depth = 0;

    for (int &c : g[centroid])
    {
        if (!processed[c])
        {
            get_cnt(c, centroid, 0);
            get_cnt(c, centroid, 1);
        }
    }
    fill(cnt + 1, cnt + 1 + max_depth, 0);
    for (int &c : g[centroid])
    {
        if (!processed[c])
            centroid_decomposition(c);
    }
}

void _144()
{
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    centroid_decomposition(1);
    cout << res;

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

    int t = 1;
    // cin >> t;
    while (t--)
    {
        _144();
    }
}
