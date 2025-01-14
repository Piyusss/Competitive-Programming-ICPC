//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//--------------------------------WRITE_HERE-------------------------------------------

vector<ll>g[200000+1];
vector<ll>subtree_size(200000+1);

ll preprocess_subtree_size(ll node,ll p){
    subtree_size[node] = 1;
    for(auto &c:g[node]){
        if(c!=p){
            subtree_size[node] += preprocess_subtree_size(c, node);;
        }
    }

    return subtree_size[node];
}

ll centroidDfs(ll node,ll p,ll n){
    for(auto &c:g[node]){
        if(c!=p){
            if(subtree_size[c] > n/2){
                return centroidDfs(c,node,n);
            }
        }
    }

    return node;
}

void _144()
{
    ll n;cin>>n;

    for(int i=0;i<n-1;i++){
        ll a,b;
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    preprocess_subtree_size(1,-1);

    cout << centroidDfs(1, -1, n);

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
    // cin >> t;
    while (t--)
    {
        _144();
    }
}
