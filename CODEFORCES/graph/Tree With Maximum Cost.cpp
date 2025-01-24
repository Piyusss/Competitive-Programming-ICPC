//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<int>g[200000+1];
vector<ll> cost(200000 + 1);
vector<int> values(200000+1);
vector<ll> sum(200000 + 1);
ll res = 0;

void preCalc(int node,int p){
    cost[node]=0;
    sum[node]=values[node];

    for(int &c:g[node]){
        if(c!=p){
            preCalc(c,node);
            sum[node]+=sum[c];
            cost[node]+=(cost[c]+sum[c]);
        }
    }
}

void dfs(int node,int p){
    res=max(res,cost[node]);

    for(int &c:g[node]){
        if(c!=p){
            sum[node] -= sum[c];
            cost[node] -= (cost[c] + sum[c]);

            sum[c] += sum[node];
            cost[c] += (cost[node] + sum[node]);

            dfs(c,node);

            sum[c] -= sum[node];
            cost[c] -= (cost[node] + sum[node]);

            sum[node] += sum[c];
            cost[node] += (cost[c] + sum[c]);
        }
    }
}

void _144()
{
    int n;cin>>n;

    for(int i=1;i<=n;i++){
        cin>>values[i];
    }

    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    preCalc(1,-1);
    dfs(1,-1);

    cout<<res;
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
    // cin >> t;
    while (t--)
    {
        _144();
    }
}
