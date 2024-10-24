//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
//--------------------------------WRITE_HERE-------------------------------------------
 
class DisjointSet
{
    vector<int> rank, parent, sizee;
    int noOfComponents;
 
public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        sizee.resize(n + 1);
        noOfComponents=n;
 
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
            sizee[i] = 1;
        }
    }
 
    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }
 
    void unionByRank(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;
        if (rank[ulp_u] < rank[ulp_v])
        {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u])
        {
            parent[ulp_v] = ulp_u;
        }
        else
        {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
 
    void unionBySize(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;
        if (sizee[ulp_u] < sizee[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            sizee[ulp_v] += sizee[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            sizee[ulp_u] += sizee[ulp_v];
        }
        noOfComponents--;
    }
 
    int sizeOfComponent(int ult_p)
    {
        return sizee[ult_p];
    }
    int findNoOfComponents(){
        return noOfComponents;
    }
 
};
 
void _144()
{
    ll n,m;
    cin>>n>>m;
 
    DisjointSet ds(n);
 
    int maxi=0;
        for (int i = 1; i <= m; i++)
    {
        ll u,v;
        cin>>u>>v;
 
        ds.unionBySize(u,v);
        int s=ds.sizeOfComponent(ds.findUPar(u));
        maxi=max(maxi,s);
        cout<<ds.findNoOfComponents()<<" ";
        cout<<maxi;
        cout<<endl;
 
    }
 
    return;
}
 
//--------------------------------END--------------------------------------------------
 
// Main
int main()
{
 
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
