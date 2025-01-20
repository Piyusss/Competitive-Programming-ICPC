//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
//--------------------------------WRITE_HERE-------------------------------------------
 
void _144()
{
    ll n,m;
    cin>>n>>m;
 
    vector<int>adjList[n+1];
 
    for(int i=0;i<m;i+=1){
        ll u,v;
        cin>>u>>v;
        adjList[u].push_back(v);
    }
 
    vector<int>indegree(n+1,0);
    for(int i=1;i<=n;i+=1){
        for(auto &it:adjList[i]){
            indegree[it]+=1;
        }
    }
 
    queue<int>q;
    for(int i=1;i<=n;i+=1){
        if(indegree[i]==0){
            q.push(i);
        }
    }
 
    vector<int>res;
    while(!q.empty()){
        auto node=q.front();
        q.pop();
 
        res.push_back(node);
 
        for(auto &it:adjList[node]){
            indegree[it]-=1;
            if(indegree[it]==0) q.push(it);
        }
    }
 
    if(res.size() != n) {
        cout<<"IMPOSSIBLE"; 
        return;
    }
 
    for(int i=0;i<n;i+=1) cout<<res[i]<<" ";
    return;
 
 
}
 
//--------------------------------END--------------------------------------------------
 
// Main
int main()
{
    // freopen("mootube.in", "r", stdin);
    // freopen("mootube.out", "w", stdout);
 
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
