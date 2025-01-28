//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
const int MAXN=2E5+1;
vector<int>g[MAXN];
int noOfBridges=0;
vector<int>level(MAXN);
vector<pair<int,int>>store;
int dp[MAXN];

void bridgeDfs(int node,int p){

    for(auto &c:g[node]){
        if (level[c] == 0)
        {
            store.push_back({node, c});
            level[c] = level[node] + 1;
            bridgeDfs(c, node);
            dp[node] += dp[c];
        }
        else{
            if(c!=p){
                if (level[c] < level[node])
                {
                    dp[node]++;
                }
                else if (level[c] > level[node])
                {
                    dp[node]--;
                    store.push_back({c, node});
                }
            }
        }

    }

    if(level[node]>=2 && dp[node]==0){
        noOfBridges++;
    }
}

void _144()
{
    int n,m;cin>>n>>m;

    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    level[1]=1;
    memset(dp,0,sizeof(dp));
    bridgeDfs(1,-1);

    // for(int i=1;i<=n;i++) cout<<level[i]<<" ";
    // cout<<endl;

    if(noOfBridges>=1){
        cout<<"0"<<"\n";
        return;
    }
    else{
        int s=store.size();
        for(int i=0;i<s;i++){
            int u=store[i].first;
            int v=store[i].second;
            cout<<u<<" "<<v<<"\n";
        }
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
    // cin >> t;
    while (t--)
    {
        _144();
    }
}
