//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<ll>res;

void eulerianDfs(ll node,vector<vector<pair<ll,ll>>>&g,vector<ll>&deg,vector<bool>&seen){
    while(!g[node].empty()){
        ll child=g[node].back().first;
        ll idx=g[node].back().second;
        
        g[node].pop_back();
        if(seen[idx]) continue;

        seen[idx]=1;
        eulerianDfs(child,g,deg,seen);
    }
    res.push_back(node);
}

void _144()
{
    ll n,m;
    cin>>n>>m;

    vector<vector<pair<ll,ll>>>g(n);
    vector<ll>deg(n);
    vector<bool>seen(m);
    
    for(ll i=0;i<m;i+=1){
        ll a,b;
        cin>>a>>b;

        a-=1;b-=1;
        deg[a]+=1;deg[b]+=1;
        g[a].push_back({b,i});
        g[b].push_back({a,i});
    }

    for(ll i=0;i<n;i+=1){
        if(deg[i]&1){
            cout<<"IMPOSSIBLE";
            return;
        }
    }

    eulerianDfs(0,g,deg,seen);

    if(m+1 != res.size()){
        cout<<"IMPOSSIBLE";
        return;
    }

    for(auto &it:res){
        cout<<it+1<<" ";
    }

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
