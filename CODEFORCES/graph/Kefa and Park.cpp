//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------
int n,m;
vector<int>cats(200000+1);
vector<int>g[200000+1];
int res=0;

void dfs(int node,int p,int curCnt){
    if(curCnt>m) return;

    bool flag=0;
    for(auto &c:g[node]){
        if(c!=p){
            bool iscCat=cats[c]==1;
            flag=1;
            dfs(c,node,(iscCat ? curCnt+1 : 0));
        }
    }

   if(flag==0) res+=1;
}

void _144()
{
    cin>>n>>m;

    for(int i=1;i<=n;i++) 
    cin>>cats[i];

    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1,-1,(cats[1]==1 ? 1 : 0));

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
