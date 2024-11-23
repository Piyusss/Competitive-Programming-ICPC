#include <bits/stdc++.h>
using namespace std; 

int n,q; 
const int mxn = 1e5 + 5, mxe = log2(mxn) + 5; 
vector<vector<int>> adj; 
int up[mxn][mxe]; 
bool vis[mxn];

void dfs(int v, int p) {
    up[v][0] = p;
    vis[v] = 1;
    for(int u: adj[v]) if(!vis[u]) dfs(u,v);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
     
    cin >> n >> q; 
    adj.resize(n);
    
    for(int i = 0; i < n - 1; ++i) {
        int a,b; cin >> a >> b, --a, --b; 
        adj[a].emplace_back(b), adj[b].emplace_back(a); 
    } 
    
    memset(up, -1, sizeof(up));
    dfs(0,-1);
    
    for(int l = 1; l < mxe; ++l) 
        for(int i = 0; i < n; ++i) 
            if(up[i][l-1] != -1) up[i][l] = up[up[i][l-1]][l-1];
    
    for(int i = 0; i < q; ++i) { 
        int node, k; cin >> node >> k, --node; 
        for(int l = 0; l < mxe; ++l) 
            if(node != -1) if(k & (1 << l)) 
                node = up[node][l];
        cout << ++node << "\n";
    } 
}
