//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<ll>res;
void eulerianDfs(ll node, vector<vector<ll>> &g)
{
    while (!g[node].empty())
    {
        ll child = g[node].back();
        g[node].pop_back();
        eulerianDfs(child, g);
    }
    res.push_back(node & 1);
}

void _144()
{
    ll n;
    cin>>n;

    if(n==1){
        cout<<"10";
        return;
    }

    ll noOfNodes=1<<(n-1);
    vector<vector<ll>> adj(noOfNodes);
    for(ll i=0;i<noOfNodes;i+=1){
        ll child= (i<<1) % (noOfNodes);

        adj[i].push_back(child); //append-0
        adj[i].push_back(child|1); //append-1
        
    }

    eulerianDfs(0,adj);
    for(ll i=1;i<=n-2;i+=1) res.push_back(0);
    for(auto &it:res) cout<<it;

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
