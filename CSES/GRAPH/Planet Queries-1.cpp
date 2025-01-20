//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
//--------------------------------WRITE_HERE-------------------------------------------
 
int up[200000+5][30];
 
int getKthAncestorNotExactlyThough(int node,int k){
    for(int bit=0;bit<=29;bit+=1){
        if((1<<bit) & k){
            node=up[node][bit];
        }
    }
    return node;
}
 
void _144()
{
    ll n,q;
    cin>>n>>q;
 
    for(int i=1;i<=n;i+=1){
        cin>>up[i][0];
    }
 
    for(int level=1;level<=29;level+=1){
        for(int node=1;node<=n;node+=1){
            up[node][level]=up[up[node][level-1]][level-1];
        }
    }
 
    while(q--){
        int x,k;
        cin>>x>>k;
        cout<<getKthAncestorNotExactlyThough(x,k)<<endl;
    }
}
 
//--------------------------------END--------------------------------------------------
 
// Main
int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.out", "w", stdout);
 
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
