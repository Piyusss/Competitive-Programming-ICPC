//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

ll n,a,b;
vector<ll>g[200000+1];
vector<ll>subord(200000+1);
vector<ll>sumThrough(200000+1);

void dfs1(ll node,ll p,ll d){
    subord[node]=1;
    sumThrough[1]+=d;

    for(auto &c:g[node]){
        if(c!=p){
            dfs1(c,node,d+1);
            subord[node] += subord[c];
        }
    }
}

void dfs2(ll node,ll p){
    for(auto &c:g[node]){
        if(c!=p){
            sumThrough[c] += sumThrough[node] + n - 2 * subord[c];//imp-transition
            dfs2(c,node);
        }
    }
}

void _144()
{
    cin>>n;

    for(ll i=0;i<n-1;i++){
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs1(1,-1,0);
    dfs2(1,-1);

    for(ll i=1;i<=n;i+=1) cout<< sumThrough[i]<<" ";

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
