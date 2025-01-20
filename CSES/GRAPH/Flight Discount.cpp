//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define pb push_back
 
vector<vector<ll>> dir = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
 
//--------------------------------WRITE_HERE-------------------------------------------
 
vector<ll> dis1(100000 + 1, 1e18);
vector<ll> dis2(100000 + 1, 1e18);
 
vector<pair<ll, ll>> adjList1[100000 + 1];
vector<pair<ll, ll>> adjList2[100000 + 1];
 
void f(vector<ll> &dis, ll s, vector<pair<ll, ll>> adjList[])
{
    set<pair<ll,ll>>pq;
    pq.insert({0, s});
 
    dis[s] = 0;
 
    while (!pq.empty())
    {
        ll d = pq.begin()->first;
        ll node = pq.begin()->second;
 
        pq.erase(pq.begin());
 
        for (auto it : adjList[node])
        {
            ll adjNode = it.first;
            ll adjDis = it.second;
 
            if (dis[node] + adjDis < dis[adjNode])
            {
                pq.erase({dis[adjNode], adjNode});
                dis[adjNode] = dis[node] + adjDis;
                pq.insert({dis[adjNode], adjNode});
            }
        }
    }
}
 
void _144()
{
    ll n, m;
    cin >> n >> m;
 
    vector<pair<pair<ll, ll>, ll>> edges;
 
    for (ll i = 1; i <= m; i++)
    {
        ll u, v, c;
        cin >> u >> v >> c;
 
        adjList1[u].pb({v, c});
        adjList2[v].pb({u, c});
        edges.pb({{u, v}, c});
    }
 
    f(dis1, 1, adjList1);
    f(dis2, n, adjList2);
 
    ll mini = 1e18;
    for (auto it : edges)
    {
        ll u = it.first.first;
        ll v = it.first.second;
        ll d = it.second;
 
        mini = min(mini, dis1[u] + dis2[v] + d / 2);
    }
 
    cout << mini;
    return;
}
 
//--------------------------------END--------------------------------------------------
 
// Main
int main()
{
 
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
