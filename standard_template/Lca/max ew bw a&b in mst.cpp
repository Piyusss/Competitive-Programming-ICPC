//Refrence:https://github.com/Piyusss/Competitive-Programming-ICPC/blob/main/CSES/Advanced%20Techniques/New%20Roads%20Queries.cpp


class LCA
{
    vector<int> dep;
    vector<vector<int>> par, val;
    vector<pair<int, int>> *graph;
    int nodeCount;

public:
    LCA(vector<pair<int, int>> *g, int n)
        : graph(g), nodeCount(n), dep(n + 1, -1),
          par(n + 1, vector<int>(LOGN, 0)),
          val(n + 1, vector<int>(LOGN, 0)) {}

    void dfs_init(int u, int p, int d)
    {
        dep[u] = d;
        par[u][0] = p;
        for (auto &it : graph[u])
        {
            int v = it.first;
            int w = it.second;
            if (v != p)
            {
                val[v][0] = w;
                dfs_init(v, u, d + 1);
            }
        }
    }

    void init()
    {
        for (int i = 1; i <= nodeCount; i++)
        {
            if (dep[i] == -1)
            {
                dfs_init(i, i, 0);
            }
        }

        for (int k = 1; k < LOGN; k++)
        {
            for (int i = 1; i <= nodeCount; i++)
            {
                par[i][k] = par[par[i][k - 1]][k - 1];
                val[i][k] = max(val[i][k - 1], val[par[i][k - 1]][k - 1]);
            }
        }
    }

    int query(int a, int b)
    {
        if (dep[a] > dep[b])
        {
            swap(a, b);
        }

        int ans = 0;
        for (int d = LOGN - 1; d >= 0; d--)
        {
            if (dep[b] - (1 << d) >= dep[a])
            {
                ans = max(ans, val[b][d]);
                b = par[b][d];
            }
        }

        if (a == b)
        {
            return ans;
        }

        for (int d = LOGN - 1; d >= 0; d--)
        {
            if (par[a][d] != par[b][d])
            {
                ans = max(ans, val[a][d]);
                ans = max(ans, val[b][d]);
                a = par[a][d];
                b = par[b][d];
            }
        }

        if (par[a][0] != par[b][0])
            return -1;

        ans = max(ans, val[a][0]);
        ans = max(ans, val[b][0]);

        return ans;
    }
};
