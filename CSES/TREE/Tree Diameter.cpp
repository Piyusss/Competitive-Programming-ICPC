//Method 01: Dp on Trees
//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

const int MAXN=200000+1;
vector<int>g[MAXN];
int res=0;
int dp[MAXN][2];

void dfs(int node,int p){
    vector<int>all;

    for(auto &c:g[node]){
        if(c!=p){
            dfs(c,node);
            all.push_back(dp[c][0]);
        }
    }

    sort(all.rbegin(),all.rend());
    int sz=all.size();

    if(sz>=1){
        dp[node][0]=all[0]+1;
    }
    if(sz>=2){
        dp[node][1]=(all[0]+1) + (1+all[1]);
    }

    res=max(res,max(dp[node][0],dp[node][1]));
}

void _144()
{
    int n;cin>>n;
    memset(dp,0,sizeof(dp));

    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
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









//Method-02: Twice Dfs
//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<ll>g[200000+1];
vector<ll>dis(200000+1);

void dfs(ll node,ll p){
    for(auto &c:g[node]){
        if(c!=p){
            dis[c]=dis[node]+1;
            dfs(c,node);
        }
    }
}

void _144()
{
    ll n;
    cin>>n;

    for(ll i=1;i<=n-1;i++){
        ll a,b;
        cin>>a>>b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1,-1);

    ll firstFarNode=-1;
    ll maxi=0;
    for(ll i=1;i<=n;i++){
        if(dis[i] > maxi){
            maxi=dis[i];
            firstFarNode=i;
        }
    }

    for(ll i=1;i<=n;i++) dis[i]=0;

    ll res = 0;
    dfs(firstFarNode,-1);
    for(ll i=1;i<=n;i++) res=max(res,dis[i]);

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
