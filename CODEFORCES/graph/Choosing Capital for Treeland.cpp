//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<pair<int,bool>>g[200000+1];
vector<int>up(200000+1),down(200000+1),cost(200000+1);
int totalUp=0;

void dfs(int node,int p){

    for(auto &c:g[node]){
        int v=c.first;
        bool dir=c.second;

        if(v!=p){
            if(dir==1) totalUp+=1;
            
            down[v]=down[node];
            if(!dir) down[v]+=1;

            up[v]=up[node];
            if(dir) up[v]+=1;

            dfs(v,node);
        }
    }
}

void _144()
{
    int n;cin>>n;

    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back({v,0});
        g[v].push_back({u,1});
    }

    dfs(1,-1);

    for(int i=1;i<=n;i++){
        cost[i]=down[i] + (totalUp-up[i]);
    }

    int res=INT_MAX;
    for(int i=1;i<=n;i++){
        res=min(res,cost[i]);
    }

    cout<<res<<"\n";
    for(int i=1;i<=n;i++){
        if(cost[i]==res){
            cout<<i<<" ";
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
