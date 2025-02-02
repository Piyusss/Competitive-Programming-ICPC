#include <bits/stdc++.h>
using namespace std;

struct TECC {
    int n, componentCount;
    vector<vector<int>> graph, teccTree;
    vector<bool> visited;
    vector<int> component, discoveryTime, lowLink;
    vector<pair<int, int>> bridges;

    void findBridges(int node, int parent, int &time) {
        visited[node] = true;
        discoveryTime[node] = lowLink[node] = time++;
        bool multipleEdges = false;
        
        for (int neighbor : graph[node]) {
            if (visited[neighbor]) {
                if (neighbor != parent || multipleEdges)
                    lowLink[node] = min(lowLink[node], discoveryTime[neighbor]);
                else
                    multipleEdges = true;
                continue;
            }
            findBridges(neighbor, node, time);
            lowLink[node] = min(lowLink[node], lowLink[neighbor]);
        }
    }

    void assignComponents(int node, int compId) {
        component[node] = compId;
        for (int neighbor : graph[node]) {
            if (component[neighbor] != -1) continue;
            if (discoveryTime[node] < lowLink[neighbor]) {
                bridges.emplace_back(node, neighbor);
                assignComponents(neighbor, ++componentCount);
            } else {
                assignComponents(neighbor, compId);
            }
        }
    }

    TECC(const vector<vector<int>> &g) : graph(g), n(g.size()), visited(n, false), component(n, -1), discoveryTime(n), lowLink(n), componentCount(0) {
        int time = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                findBridges(i, -1, time);
                assignComponents(i, componentCount++);
            }
        }
    }

    void buildTeccTree() {
        teccTree.resize(componentCount);
        for (auto &[u, v] : bridges) {
            int cu = component[u], cv = component[v];
            teccTree[cu].push_back(cv);
            teccTree[cv].push_back(cu);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    TECC tecc(graph);
    vector<vector<int>> components(tecc.componentCount);
    
    for (int i = 0; i < n; i++) {
        components[tecc.component[i]].push_back(i);
    }
    
    cout << components.size() << '\n';
    for (const auto &comp : components) {
        cout << comp.size();
        for (int node : comp) cout << ' ' << node;
        cout << '\n';
    }
    
    return 0;
}
