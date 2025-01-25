//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
const int MAXN=3E5+1;
vector<pair<int,int>>g[MAXN];
vector<int>gas(MAXN);
ll dp[MAXN][2];
ll res=0;

void dfs(int node,int p){
    vector<ll>all;

    for(auto &it:g[node]){
        int c=it.first;
        int w=it.second;
        if(c!=p){
            dfs(c,node);
            if(dp[c][0]-w>0) all.push_back(dp[c][0]-w);
        }
    }

    sort(all.rbegin(),all.rend());
    int sz=all.size();

    if(sz>=1) dp[node][0]=all[0]+gas[node];
    if(sz>=2) dp[node][1]=(all[0]) + (gas[node]) + (all[1]);

    res=max(res,max(dp[node][0],dp[node][1]));
}

void _144()
{
    int n;cin>>n;

    for(int i=1;i<=n;i++){
        cin>>gas[i];
        dp[i][0]=dp[i][1]=gas[i];
    }

    if(n==1){
        cout<<gas[1];
        return;
    }

    for(int i=0;i<n-1;i++){
        int u,v,w;cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

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
