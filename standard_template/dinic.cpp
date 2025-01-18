struct Edge
{
    int v;       
    ll capacity; 
    ll flow;     
};

class DINIC
{
private:
    int V;                    
    vector<Edge> EL;         
    vector<vector<int>> AL;  
    vector<int> d, last;      
    vector<pair<int, int>> p; 

    bool BFS(int s, int t)
    {
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        p.assign(V, {-1, -1});
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u == t)
                break;
            for (int idx : AL[u])
            {
                Edge &e = EL[idx];
                if (e.capacity > e.flow && d[e.v] == -1)
                {
                    d[e.v] = d[u] + 1;
                    q.push(e.v);
                    p[e.v] = {u, idx};
                }
            }
        }
        return d[t] != -1;
    }

    ll DFS(int u, int t, ll f)
    {
        if (u == t || f == 0)
            return f;
        for (int &i = last[u]; i < AL[u].size(); ++i)
        {
            int idx = AL[u][i];
            Edge &e = EL[idx];
            Edge &rev = EL[idx ^ 1];
            if (d[e.v] != d[u] + 1)
                continue;
            ll pushed = DFS(e.v, t, min(f, e.capacity - e.flow));
            if (pushed > 0)
            {
                e.flow += pushed;
                rev.flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

public:
    DINIC(int n)
    {
        V = n;
        EL.clear();
        AL.resize(n);
    }

    //0-based
    void add_edge(int u, int v, ll w)
    {
        if (u == v)
            return;              
        EL.push_back({v, w, 0});
        AL[u].push_back(EL.size() - 1);
        EL.push_back({u, 0, 0}); 
        AL[v].push_back(EL.size() - 1);
    }

    //0-based
    ll get_max_flow(int s, int t)
    {
        ll mf = 0;
        while (BFS(s, t))
        {
            last.assign(V, 0);
            while (ll f = DFS(s, t, INF))
            {
                mf += f;
            }
        }
        return mf;
    }
};
