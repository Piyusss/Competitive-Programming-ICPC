#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MX = 2e5 + 5;
priority_queue<ll> bes[MX];
vector<pair<int, int>> adj[MX];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    int n,m,k;
    cin>>n>>m>>k;
	for(int i=0;i<m;i+=1){
		int a,b,c;
		cin>>a>>b>>c;
		adj[a].push_back({b,c});
	}

	bes[1].push(0);
	pq.push({0,1});

	while(!pq.empty()) {
		auto a=pq.top();
		pq.pop();

		if(a.first > bes[a.second].top()) continue;

		for(auto &i:adj[a.second]) {
			ll tmp=a.first+i.second;
			if(bes[i.first].size() < k){
				bes[i.first].push(tmp);
				pq.push({tmp, i.first});
			}
            else if(tmp < bes[i.first].top()){
				bes[i.first].pop();
				bes[i.first].push(tmp);
				pq.push({tmp,i.first});
			}
		}
	}

	vector<ll> ans;
	while (!bes[n].empty()) {
		ans.push_back(bes[n].top());
		bes[n].pop();
	}

	reverse(ans.begin(), ans.end());
	for(auto &it:ans) cout<<it<<" ";

    return 0;

}
