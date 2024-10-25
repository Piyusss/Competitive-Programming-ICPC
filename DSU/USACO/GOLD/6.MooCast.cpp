Approach 1:
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
