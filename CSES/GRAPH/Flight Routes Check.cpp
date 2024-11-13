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

void dfs2(int node,vector<int>&vis,vector<int>adjListRev[]){
    vis[node]=1;

    for(auto &it:adjListRev[node]){
        if(!vis[it]){
            dfs2(it,vis,adjListRev);
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
    vector<int>roots;
    while(!st.empty()){
        auto it=st.top();
        st.pop();
        if(vis[it]) continue;

        roots.push_back(it);
        dfs2(it,vis,adjListRev);
        noOfScc+=1;
    }

    if(noOfScc==1){
        cout<<"YES";
        return;
    }

    cout<<"NO"<<endl;
    cout << roots[1] << " " << roots[0];
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
