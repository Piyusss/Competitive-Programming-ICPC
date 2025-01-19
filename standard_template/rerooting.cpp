class Reroot
{
public:
    using Aggregate = long long; // Change to `int` for max/min
    using Value = long long;

    Reroot(vector<vector<int>> &graph, vector<int> &node_values)
        : g(graph), values(node_values), n((int)graph.size())
    {
        dp.resize(n);
        parent.resize(n, -1);
        bfs.reserve(n);
    }

    vector<long long> solve()
    {
        compute_initial_dp();
        compute_reroot_dp();
        return dp;
    }

private:
    int n;
    vector<vector<int>> g;
    vector<int> values;
    vector<long long> dp;
    vector<int> parent, bfs;

    void compute_initial_dp()
    {
        bfs.push_back(0);
        for (int i = 0; i < n; ++i)
        {
            int u = bfs[i];
            for (int v : g[u])
            {
                if (v == parent[u])
                    continue;
                parent[v] = u;
                bfs.push_back(v);
            }
        }

        for (int i = n - 1; i >= 0; --i)
        {
            int u = bfs[i];
            dp[u] = values[u];
            for (int v : g[u])
            {
                if (v == parent[u])
                    continue;
                dp[u] += dp[v]; // Change this to max/min for other operations
            }
        }
    }

    void compute_reroot_dp()
    {
        for (int u : bfs)
        {
            for (int v : g[u])
            {
                if (v == parent[u])
                    continue;

                dp[u] -= dp[v];
                dp[v] += dp[u]; // Change this to max/min as needed
                parent[u] = v;
                parent[v] = u;

                dp[v] -= dp[u];
                dp[u] += dp[v]; // Restore values for next sibling
            }
        }
    }
};
