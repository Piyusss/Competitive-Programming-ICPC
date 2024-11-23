//@memset.DP.-1
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll M=(ll)1E9+7;
//--------------------------------WRITE_HERE-------------------------------------------


void _144()
{
    ll n,m;
    cin>>n>>m;

    vector<pair<ll,ll>>adjList[n+1];
    for(ll i=0;i<m;i+=1){
        ll u,v,c;
        cin>>u>>v>>c;
        adjList[u].push_back({v,c});
    }

    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,
    greater<pair<ll,ll>>>pq;
    pq.push({0,1});

    vector<ll>dis(n+1,LLONG_MAX),minCost_flights(n+1,0),
    minNumOfFlights(n+1,0),maxNumOfFlights(n+1,0);
    dis[1]=0;
    minCost_flights[1]=1;
    minNumOfFlights[1]=0;
    maxNumOfFlights[1]=0;

    while(!pq.empty()){
        auto it=pq.top();
        ll node=it.second;
        ll d=it.first;
        pq.pop();

        if(dis[node]<d) continue;

        for(auto &child:adjList[node]){
            ll adjNode=child.first;
            ll adjWt=child.second;

            if(d+adjWt<dis[adjNode]){
                dis[adjNode]=d+adjWt;
                minCost_flights[adjNode]=minCost_flights[node];
                minNumOfFlights[adjNode]=minNumOfFlights[node]+1;
                maxNumOfFlights[adjNode]=maxNumOfFlights[node]+1;
                pq.push({dis[adjNode],adjNode});
            }
            else if(d+adjWt==dis[adjNode]){
                minCost_flights[adjNode] += minCost_flights[node];
                minCost_flights[adjNode] %= M;
                minNumOfFlights[adjNode]=min(minNumOfFlights[adjNode],minNumOfFlights[node]+1);
                maxNumOfFlights[adjNode]=max(maxNumOfFlights[adjNode],maxNumOfFlights[node]+1);
            }
        }
    }

    cout<<dis[n]<<" "<<minCost_flights[n]<<" "<<minNumOfFlights[n]<<" "<<maxNumOfFlights[n];
    return;
}

//--------------------------------END--------------------------------------------------

// Main
int main()
{
	//freopen("input.in", "r", stdin);
	//freopen("output.out", "w", stdout);

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
