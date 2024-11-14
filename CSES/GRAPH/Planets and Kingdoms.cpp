//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

void dfs(int node,vector<int>&vis,stack<int>&st,vector<int>adjList[]){
    vis[node]=1;

    for(auto &it:adjList[node]){
        if(!vis[it]){
            dfs(it,vis,st,adjList);
        }
    }
    st.push(node);
}

void dfs2(int node,vector<int>&vis,vector<int>adjListRev[]
,int kingdomNo,vector<int>&roots){
    vis[node]=1;
    roots[node]=kingdomNo;

    for(auto &it:adjListRev[node]){
        if(!vis[it]){
            dfs2(it,vis,adjListRev,kingdomNo,roots);
        }
    }
}

void _144()
{
    ll n,m;
    cin>>n>>m;

    vector<int>adjList[n+1];
    for(int i=0;i<m;i++){
        ll u,v;
        cin>>u>>v;
        adjList[u].push_back(v);
    }

    stack<int>st;
    vector<int>vis(n+1,0);
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i,vis,st,adjList);
        }
    }
    
    vector<int>adjListRev[n+1];
    for(int i=1;i<=n;i++){
        vis[i]=0;
        for(auto &it:adjList[i]){
            adjListRev[it].push_back(i);
        }
    }

    int noOfScc=0;
    int kingdomNo=1;
    vector<int> roots(n+1,-1);

    while(!st.empty()){
        auto it=st.top();
        st.pop();
        if(vis[it]) continue;

        dfs2(it,vis,adjListRev,kingdomNo,roots);
        noOfScc+=1;
        kingdomNo += 1;
    }

    cout << noOfScc << endl;
    for(int i=1;i<=n;i++) cout<<roots[i]<<" ";
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
