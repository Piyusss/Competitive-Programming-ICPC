//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll M=1E9+7;
//--------------------------------WRITE_HERE-------------------------------------------

void _144()
{
    ll n,m;
    cin>>n>>m;

    vector<int>adjList[n+1],indegree(n+1);
    vector<vector<int>>backs(n+1);
    for(int i=0;i<m;i+=1){
        ll u,v;
        cin>>u>>v;
        adjList[u].push_back(v);
        indegree[v]+=1;
        backs[v].push_back(u);
    }

    //start kahns
    queue<int>q;
    for(int i=1;i<=n;i+=1) if(indegree[i]==0) q.push(i);

    vector<int>topo;
    while(!q.empty()){
        auto it=q.front();
        q.pop();

        topo.push_back(it);

        for(auto &child:adjList[it]){
            indegree[child] -= 1;
            if(indegree[child]==0) q.push(child);
        }
    }

    vector<int>dp(n+1,0);
    dp[1]=1;
    for(auto &it:topo){
        for(auto &it2:backs[it]){
            dp[it] = (dp[it]+dp[it2]) % M;
        }
    }

    cout<<dp[n];
    return;

}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
	//freopen("input.in", "r", stdin);
	//freopen("output.out", "w", stdout);

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
