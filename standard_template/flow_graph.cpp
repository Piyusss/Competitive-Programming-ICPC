typedef pair<ll, ll> pii;
const ll INF = 0x3f3f3f3f;

class FlowGraph
{
private:
    ll N, M;
    vector<vector<ll>> capacity;
    vector<vector<ll>> adjList;
    vector<vector<pii>> edgeList;
    vector<ll> parent;
    vector<bool> visitedEdges;

public:
    FlowGraph(ll n, ll m) : N(n), M(m)
    {
        capacity.assign(N + 1, vector<ll>(N + 1, 0));
        adjList.assign(N + 1, vector<ll>());
        edgeList.assign(N + 1, vector<pii>());
        parent.assign(N + 1, -1);
        visitedEdges.assign(M, false);
    }

    void addEdge(ll a, ll b, ll weight, ll id)
    {
        edgeList[a].push_back({b, id});
        adjList[a].push_back(b);
        adjList[b].push_back(a);
        capacity[a][b] += weight;
    }

    ll bfs(ll s, ll t)
    {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;

        queue<pii> q;
        q.push({s, INF});

        while (!q.empty())
        {
            ll u = q.front().first;
            ll flow = q.front().second;
            q.pop();

            for (ll v : adjList[u])
            {
                if (parent[v] == -1 && capacity[u][v] > 0)
                {
                    parent[v] = u;
                    ll aug = min(flow, capacity[u][v]);
                    if (v == t)
                        return aug;
                    q.push({v, aug});
                }
            }
        }
        return 0;
    }

    ll maxFlow(ll s, ll t)
    {
        ll totalFlow = 0, augFlow;

        while ((augFlow = bfs(s, t)) > 0)
        {
            totalFlow += augFlow;
            ll u = t;

            while (u != s)
            {
                ll v = parent[u];
                capacity[v][u] -= augFlow;
                capacity[u][v] += augFlow;
                u = v;
            }
        }

        return totalFlow;
    }

    void dfs(ll u, vector<ll> &path, ll t)
    {
        path.push_back(u);
        if (u == t)
            return;

        for (const auto &edge : edgeList[u])
        {
            ll v = edge.first;
            ll id = edge.second;

            if (capacity[u][v] == 0 && !visitedEdges[id])
            {
                visitedEdges[id] = true;
                dfs(v, path, t);
                return;
            }
        }
    }

    void printPaths(ll s, ll t, ll maxFlowValue)
    {
        for (ll i = 0; i < maxFlowValue; ++i)
        {
            vector<ll> path;
            dfs(s, path, t);
            cout << path.size() << endl;
            for (size_t j = 0; j < path.size(); ++j)
            {
                cout << path[j]+1 << (j == path.size() - 1 ? '\n' : ' ');
            }
        }
    }
};
