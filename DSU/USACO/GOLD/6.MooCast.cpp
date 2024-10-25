//Approach 1: Binary Search + Floodfill/Bfs
//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

bool disCheck(vector<pair<ll,ll>>&coordinates,ll node1,ll node2,ll mid){
    ll x1=coordinates[node1].first;
    ll y1=coordinates[node1].second;
    ll x2=coordinates[node2].first;
    ll y2=coordinates[node2].second;

    ll xDif=(x2-x1);
    ll yDif=(y2-y1);

    ll dSquare= (xDif*xDif) + (yDif*yDif) ;

    return mid >= dSquare ;
}

bool check(ll mid, vector<pair<ll,ll>> &coordinates){
    int n=coordinates.size();
    vector<int>vis(n,0);
    vis[0]=1;

    queue<ll>q;
    q.push(0);

    while(!q.empty()){
        int s=q.size();
        while(s--){
            auto it=q.front();
            q.pop();

            for(int i=0;i<n;i++){
                if(it==i) continue;
                if(!vis[i] && disCheck(coordinates,it,i,mid)){
                    q.push(i);
                    vis[i]=1;
                }
            }
        }
    }

    for(auto &it:vis) if(it==0) return 0;
    return 1;
}

void _144()
{
    ll n;
    cin>>n;

    vector<pair<ll,ll>>coordinates;

    for(int i=0;i<n;i++){
        ll x,y;
        cin>>x>>y;
        coordinates.push_back({x,y});
    }

    ll low=1;
    ll high=1e9;
    ll res=-1;
    while(low<=high){
        ll mid=low + (high-low)/2;

        if(check(mid,coordinates)){
            res=mid;
            high=mid-1;
        }
        else low=mid+1;
    }

    cout<<res<<endl;
    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

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

//Approach 2:Dsu
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

static bool comp(pair<pair<ll,ll>,ll>&a,pair<pair<ll,ll>,ll>&b){
    return a.second<b.second;
}

void _144()
{
    ll n;
    cin>>n;

    vector<pair<ll,ll>>coordinates;
    for(int i=0;i<n;i++){
        ll x,y;
        cin>>x>>y;
        coordinates.push_back({x,y});
    }

    vector<pair<pair<ll,ll>,ll>>edges;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            ll x1=coordinates[i].first;
            ll y1=coordinates[i].second;
            ll x2=coordinates[j].first;
            ll y2=coordinates[j].second;

            ll xDif=x2-x1;
            ll yDif=y2-y1;
            ll d=(xDif*xDif) + (yDif*yDif);
            edges.push_back({{i,j},d});
        }
    }

    sort(edges.begin(),edges.end(),comp);

    ll tot=n;
    DisjointSet ds(n);
    for(auto &it:edges){
        ll u=it.first.first;
        ll v=it.first.second;
        ll w=it.second;
        if(ds.findUPar(u)!=ds.findUPar(v)){
            ds.unionBySize(u,v);
            tot--;
            if(tot==1){
                cout<<w<<endl;return;
            }
        }
    }

    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

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
