//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

class DisjointSet
{
    vector<int> rank, parent, sizee;

public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        sizee.resize(n + 1);
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
    }

    int sizeOfComponent(int ult_p)
    {
        return sizee[ult_p];
    }
};


void _144()
{
    ll n,a,b;
    cin>>n>>a>>b;

    DisjointSet ds(n);
    
    unordered_map<ll,ll>mp;
    vector<ll>v(n);
    for(ll i=0;i<n;i++){
        cin >> v[i];
        mp[v[i]]=i;
    }

    vector<ll>st(n);
    for(int i=0;i<n;i++){
        ll el=v[i];
        if(mp.find(a-el)!=mp.end()){
            ds.unionBySize(i,mp[a-el]);
            st[i] += 1;
        }
        if(mp.find(b-el)!=mp.end()){
            ds.unionBySize(i,mp[b-el]);
            st[i] += 2;
        }
    }

    vector<ll>final(n,3);
    for(int i=0;i<n;i++){
        final[ds.findUPar(i)] &= st[i];
        if(final[ds.findUPar(i)]==0){
            cout<<"NO"<<endl;
            return;
        }
    }

    cout << "YES" << endl;
    vector<ll> res;
    for(ll i=0;i<n;i++){
        ll val=final[ds.findUPar(i)];
        if(val==1) res.push_back(0);
        else if(val==2) res.push_back(1);
        else if(val==3) res.push_back(1);
    }
    
    for(auto &it:res) cout<<it<<" ";
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




Final Check:
If after applying the AND operation across all elements in a component, the result is 0, that means there are conflicting assignments (one part of the component wants to be in set A, another in set B), making the solution impossible.

Conclusion:
The bitwise AND operation ensures that all elements in a component agree on the same set assignment. If there's a conflict, the AND result will become 0, indicating the division is impossible. Hence, the AND operation is essential to verify consistency within a component.
