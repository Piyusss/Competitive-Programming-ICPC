//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
struct flow_network {

    struct edge {
        ll u, v, cap;
        edge *rev;
        bool forward;
        edge(ll _u, ll _v, ll _cap, bool forw)
            : u(_u), v(_v), cap(_cap), forward(forw) {}
    };

    ll n;
    vector<vector<edge*> > adj;
    flow_network(ll _n) : n(_n), adj(_n) {}

    void add_edge(ll u, ll v, ll cap) {
        edge *e = new edge(u, v, cap, true);
        edge *rev = new edge(v, u, 0, false);
        e->rev = rev;
        rev->rev = e;
        adj[u].push_back(e);
        adj[v].push_back(rev);
    }

    ll augment(ll s, ll t) {
        vector<edge*> back(n, (edge*)0);
        queue<int> Q;
        Q.push(s);
        back[s] = (edge*)1;
        while (!Q.empty()) {
            ll u = Q.front(); Q.pop();
            for (ll i = 0; i < adj[u].size(); i++) {
                ll v = adj[u][i]->v;
                if (back[v] == NULL && adj[u][i]->cap > 0) {
                    back[v] = adj[u][i];
                    Q.push(v);
                }
            }
        }

        if (back[t] == NULL)
            return 0;

        stack<edge*> S;
        S.push(back[t]);
        ll bneck = back[t]->cap;
        while (S.top()->u != s) {
            S.push(back[S.top()->u]);
            bneck = min(bneck, S.top()->cap);
        }

        while (!S.empty()) {
            S.top()->cap -= bneck;
            S.top()->rev->cap += bneck;
            S.pop();
        }

        return bneck;
    }

    ll max_flow(ll source, ll sink) {
        ll flow = 0;
        while (1) {
            ll f = augment(source, sink);
            if (f == 0) break;
            flow += f;
        }
        return flow;
    }
};


void _144()
{
    ll n,m;
    cin>>n>>m;

    flow_network net(n);

    for(ll i=0;i<m;i+=1){
        ll a,b,c;
        cin>>a>>b>>c;

        net.add_edge(--a,--b,c);
    }

    cout<<net.max_flow(0,n-1);

    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.out", "w", stdout);

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





or






#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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
                cout << path[j] + 1 << (j == path.size() - 1 ? '\n' : ' ');
            }
        }
    }
};

int main()
{
    ll n, m;
    cin >> n >> m;

    FlowGraph g(n, m);

    for (ll i = 0; i < m; ++i)
    {
        ll a, b, w;
        cin >> a >> b >> w;
        g.addEdge(--a, --b, w, i);
    }

    ll maxFlowValue = g.maxFlow(0, n - 1);
    cout << maxFlowValue << endl;

    return 0;
}
