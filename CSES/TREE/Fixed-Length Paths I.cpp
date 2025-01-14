//Method-01: O(NlogN)

//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

int n, a, b;
vector<int> graph[200001];
int subtree[200001];

ll ans = 0, bit[200001];
int total_cnt[200001]{1}, mx_depth;
int cnt[200001], subtree_depth;
bool processed[200001];

int get_subtree_sizes(int node, int parent = 0)
{
    subtree[node] = 1;
    for (int i : graph[node])
        if (!processed[i] && i != parent)
            subtree[node] += get_subtree_sizes(i, node);
    return subtree[node];
}

int get_centroid(int desired, int node, int parent = 0)
{
    for (int i : graph[node])
        if (!processed[i] && i != parent && subtree[i] >= desired)
            return get_centroid(desired, i, node);
    return node;
}

void get_cnt(int node, int parent, int depth = 1)
{
    if (depth > b)
        return;
    subtree_depth = max(subtree_depth, depth);
    cnt[depth]++;
    for (int i : graph[node])
        if (!processed[i] && i != parent)
            get_cnt(i, node, depth + 1);
}

void centroid_decomp(int node = 1)
{
    int centroid = get_centroid(get_subtree_sizes(node) >> 1, node);
    processed[centroid] = true;
    mx_depth = 0;
    long long partial_sum_init = (a == 1 ? 1ll : 0ll);
    for (int i : graph[centroid])
        if (!processed[i])
        {
            subtree_depth = 0;
            get_cnt(i, centroid);

            long long partial_sum = partial_sum_init;
            for (int depth = 1; depth <= subtree_depth; depth++)
            {
                ans += partial_sum * cnt[depth];

                int dremove = b - depth;
                if (dremove >= 0)
                    partial_sum -= total_cnt[dremove];
                int dadd = a - (depth + 1);
                if (dadd >= 0)
                    partial_sum += total_cnt[dadd];
            }

            for (int depth = a - 1; depth <= b - 1 && depth <= subtree_depth; depth++)
                partial_sum_init += cnt[depth];

            for (int depth = 1; depth <= subtree_depth; depth++)
                total_cnt[depth] += cnt[depth];
            mx_depth = max(mx_depth, subtree_depth);

            fill(cnt, cnt + subtree_depth + 1, 0);
        }
    fill(total_cnt + 1, total_cnt + mx_depth + 1, 0);
    for (int i : graph[centroid])
        if (!processed[i])
            centroid_decomp(i);
}

void _144()
{
    int k;
    cin >> n >> k;
    a = k;
    b = k;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    centroid_decomp();
    cout << ans;

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






//Method-02: O(N)

//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

const int MAX_NODES = 2e5 + 5;

vector<int> adjacency_list[MAX_NODES];
int total_nodes, a, b;
long long result = 0;

int get_prefix(const deque<int> &values, int max_index)
{
    if (max_index < 0)
        return 0;
    if (max_index + 1 >= values.size())
        return values[0];
    return values[0] - values[max_index + 1];
}

void combine(deque<int> &primary, deque<int> &secondary)
{
    if (primary.size() < secondary.size())
        swap(primary, secondary);
    for (size_t i = 0; i < secondary.size() - 1; ++i)
        secondary[i] -= secondary[i + 1];
    for (size_t i = 0; i < secondary.size(); ++i)
        result += static_cast<long long>(secondary[i]) * (get_prefix(primary, b - i) - get_prefix(primary, a - 1 - i));
    for (size_t i = secondary.size() - 1; i-- > 0;)
        secondary[i] += secondary[i + 1];
    for (size_t i = 0; i < secondary.size(); ++i)
        primary[i] += secondary[i];
}

deque<int> depth_first_search(int current_node, int parent_node)
{
    deque<int> result_values = {1};
    for (int neighbor : adjacency_list[current_node])
    {
        if (neighbor == parent_node)
            continue;
        deque<int> child_values = depth_first_search(neighbor, current_node);
        child_values.push_front(child_values.front());
        combine(result_values, child_values);
    }
    return result_values;
}

void _144()
{   int k;
    cin >> total_nodes >> k;
    a=k;b=k;
    for (int i = 0; i < total_nodes - 1; ++i)
    {
        int node_a, node_b;
        cin >> node_a >> node_b;
        adjacency_list[node_a].push_back(node_b);
        adjacency_list[node_b].push_back(node_a);
    }
    depth_first_search(1, 0);
    cout << result << "\n";

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
