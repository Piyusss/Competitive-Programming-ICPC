//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class DisjointSet
{
    vector<int> rank, parent, sizee, maxInComponent;

public:
    DisjointSet(int n,vector<int>&point)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        sizee.resize(n + 1);
        for (int i = 1; i <= n; i++)
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

    void unionBySize(int u, int v,vector<int>&point)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);

        if (ulp_u == ulp_v)
            {
                cout<<"Invalid query!"<<"\n";
                return;
            }

        if (point[ulp_u] < point[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            sizee[ulp_v] += sizee[ulp_u];
        }
        else if(point[ulp_u] > point[ulp_v]){
            parent[ulp_v] = ulp_u;
            sizee[ulp_u] += sizee[ulp_v];
        }
        else 0==0;
    }

    int sizeOfComponent(int ult_p)
    {
        return sizee[ult_p];
    }
};

void _144()
{
    int n;cin>>n;


    vector<int>point(n+1);
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        point[i]=x;
    }
    DisjointSet ds(n,point);

    int q;cin>>q;
    while(q--){
        int type;cin>>type;

        if(type==0){
            //dish number
            int x,y;cin>>x>>y;
            ds.unionBySize(x,y,point);
        }
        else{
            //dish number
            int x;cin>>x;
            int res=ds.findUPar(x);
            cout<<res<<"\n";
        }
    }

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
    cin >> t;
    while (t--)
    {
        _144();
    }
}
