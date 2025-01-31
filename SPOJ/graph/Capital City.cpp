//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

void dfs(ll node, vector<ll> &vis, stack<ll> &st, vector<ll> adjList[])
{
    vis[node] = 1;

    for (auto &it : adjList[node])
    {
        if (!vis[it])
        {
            dfs(it, vis, st, adjList);
        }
    }
    st.push(node);
}

void dfs2(ll node, vector<ll> &vis, vector<ll> adjListRev[], vector<ll> &component)
{
    vis[node] = 1;
    component.push_back(node);

    for (auto &it : adjListRev[node])
    {
        if (!vis[it])
        {
            dfs2(it, vis, adjListRev,component);
        }
    }
}

ll lastMarked=-1;

void dfsFinal(ll node,vector<ll>&visFinal,
vector<vector<ll>>&g){
    visFinal[node]=1;
    lastMarked=node;

    for(auto &c:g[node]){
        if(!visFinal[c]){
            dfsFinal(c,visFinal,g);
        }
    }
}

void _144()
{
    ll n, m;
    cin >> n >> m;

    vector<ll> adjList[n + 1];
    for (ll i = 0; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
    }

    stack<ll> st;
    vector<ll> vis(n + 1, 0);
    for (ll i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i, vis, st, adjList);
        }
    }

    vector<ll> adjListRev[n + 1];
    for (ll i = 1; i <= n; i++)
    {
        vis[i] = 0;
        for (auto &it : adjList[i])
        {
            adjListRev[it].push_back(i);
        }
    }

    ll id = 0;
    vector<ll> roots(n + 1, 0);
    unordered_map<ll,vector<ll>>mp;
    while (!st.empty())
    {
        auto it = st.top();
        st.pop();
        if (vis[it])continue;

        vector<ll> component;
        dfs2(it, vis, adjListRev,component);
        for(auto &u:component){
            roots[u] = id;
        }
        mp[id]=component;
        id+=1;
    }

    //Make Condensation Graph
    vector<vector<ll>> adjCond;
    adjCond.assign(n+1,{});
    for (ll v = 1; v <= n; v++)
    {
        for (auto &u : adjList[v]){
            if (roots[v] != roots[u]){
                adjCond[roots[v]].push_back(roots[u]);
            }
        }
    }

    vector<ll>visFinal(n+1,0);
    dfsFinal(1, visFinal, adjCond);

    ll capitalComp=lastMarked;
    vector<ll>req=mp[capitalComp];

    cout<<req.size()<<"\n";
    sort(req.begin(),req.end());
    for(auto &c:req){
        cout<<c<<" ";
    }
    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    // freopen("mootube.in", "r", stdin);
    // freopen("mootube.out", "w", stdout);

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
