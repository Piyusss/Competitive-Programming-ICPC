//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

    vector<int>dis(n+1,INT_MIN),parent(n+1,-1);
    dis[1]=1;
    for(auto &it:topo){
        for(auto &it2:backs[it]){
            if(dis[it2]+1 > dis[it]){
                dis[it]=dis[it2]+1;
                parent[it]=it2;
            }
        }
    }

    if(dis[n] < 2){
        cout<<"IMPOSSIBLE"<<endl;
        return;
    }

    vector<int>res;
    int end=n;
    res.push_back(n);
    while(1){
        if(parent[end]==-1) break;
        res.push_back(parent[end]);
        end=parent[end];
    }

    cout<<res.size()<<endl;
    for(int i=res.size()-1;i>=0;i-=1) cout<<res[i]<<" ";
    return;

}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
	//freopen("mootube.in", "r", stdin);
	//freopen("mootube.out", "w", stdout);

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
