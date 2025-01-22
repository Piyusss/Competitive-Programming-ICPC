//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class Graph
{
private:
    int V;
    vector<int> *adjList;
    int cycleEntry;

    bool dfs(int node, int parent, vector<bool> &visited)
    {
        visited[node] = true;

        for (int neighbor : adjList[node])
        {
            if (!visited[neighbor])
            {
                if (dfs(neighbor, node, visited))
                {
                    return true;
                }
            }
            else if (neighbor != parent)
            {
                cycleEntry = neighbor;
                return true;
            }
        }
        return false;
    }

    vector<int> bfs(int start)
    {
        vector<int> distance(V + 1, -1);
        queue<int> q;
        q.push(start);
        distance[start] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int neighbor : adjList[node])
            {
                if (distance[neighbor] == -1)
                {
                    distance[neighbor] = distance[node] + 1;
                    q.push(neighbor);
                }
            }
        }
        return distance;
    }

public:
    Graph(int vertices, vector<int> g[]) : V(vertices)
    {
        adjList = g;
        cycleEntry = -1;
    }

    bool canValeriuEscape(int a, int b)
    {
        vector<bool> visited(V + 1, false);

        dfs(b, -1, visited);

        vector<int> distFromMarcel = bfs(a);
        vector<int> distFromValeriu = bfs(b);

        return distFromValeriu[cycleEntry] < distFromMarcel[cycleEntry];
    }
};

void _144()
{
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> g[n + 1];
    for (int i = 0; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (a == b)
    {
        cout << "NO"<<"\n";
        return;
    }

    Graph graph(n, g);
    if (graph.canValeriuEscape(a, b))
    {
        cout << "YES"<<"\n";
    }
    else
    {
        cout << "NO"<<"\n";
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
    cin >> t;
    while (t--)
    {
        _144();
    }
}
